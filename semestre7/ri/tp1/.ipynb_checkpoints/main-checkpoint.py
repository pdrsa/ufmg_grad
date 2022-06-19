#!/usr/bin/python
# -*- coding: UTF-8 -*-
from bs4 import BeautifulSoup
from warcio.capture_http import capture_http
import requests
from queue import Queue
from reppy.robots import Robots
from url_normalize import url_normalize
from urllib.parse import urlparse
import json
import os
import idna
import getopt, sys
import multiprocessing
import time
import pickle
import signal

'''
Global Variables

domains:  Contains all crawled domains.
visited:  All visited websites
frontier: Queue containing the websites that should be crawled next
buffer:   List of tuples in format (Url, Soup, Robots)
'''
NUM_THREADS = 100
domains  = dict()
visited  = set()
frontier = Queue()
counter  = 0

# This is a handler to use with signal. If a function takes too long this exception will be raised.
def handler(signum, frame):
    raise Exception("timeout")

# Get raw html from Url and stores it in the correct Warc file
def get_html(url, id):
    warc_file = "corpus/" + str(id) + ".warc.gz"
    with capture_http(warc_file):
        return requests.get(url).text

# Get first 20 words from text within a Soup object
def get_text(soup, limit = 20):
    split = soup.get_text(separator = " ").split()
    text = ""
    for i, word in enumerate(split):
        text += word
        if(i >= limit):
            break
        text += " "

    return text

'''
Simple debugging function. Outputs in JSON format.
Input:
    url:  Url to print
    soup: Soup object from the url
    time_now: Timestamp when the Url has been accessed
'''
def print_debug(url, soup, time_now):
    debugger = dict()
    debugger['URL']       = url
    debugger['Title']     = soup.find('title').string
    debugger['Text']      = get_text(soup, limit = 20)
    debugger['Timestamp'] = int(time_now)
    json_string = json.dumps(debugger, indent = 4, ensure_ascii=False).encode('utf8')
    print(json_string.decode())

'''
Extract all eligible links from a Soup object and add them to the Queue.
Input:
    url: Url of the webpage
    soup: Soup object to extract the links from
    robots: The robots object from the url
'''
def add_links(url, soup, robots):
    main_domain = urlparse(url).netloc
    for element in soup.findAll('a'):
        link = element.get('href')
        if link and link != '/':
            if(link[0] == '/'):
                link = url + link
            domain = urlparse(link).netloc
            if not domain:
                continue

            # print("Link: ", link)
            # print("Robots: ", robots.allowed(link, '*'))
            # print("Domain: ", domain, "is on domain?", domain in domains)


            # To improve coverage, links from a domain are added only once.
            if(domain not in domains and ((robots.allowed(link, '*') or domain != main_domain))):
                normalized_link = url_normalize(link)
                if(normalized_link not in visited):
                    frontier.put(normalized_link)

'''
Visits websites and add them to the buffer.
Input:
    q:   Multiprocessing Queue i.e. reference to the buffer.
    url: Url to be visited.
    id:  Thread Id.
'''
def visit(url, id):
    try:
        # Define robots of URL
        robots_url = Robots.robots_url(url)
        # Retrieve html information
        html_text = get_html(url, id)

        return (url, html_text, robots_url)
    except Exception as e: 
        print(e)
        return None


'''
Make one iteration of the crawling process, consuming all pages stored in the buffer.
The website visited is the first element in the frontier Queue.
Visit website -> Store Data -> Add links to frontier

Input:
    debug: Defines if debug mode should be active.
'''
def crawl(buffer, debug = False):
    for x in buffer:
        signal.alarm(5)
        try:
            if not x: continue
            time_now = time.time()
            url, html_text, robots_url = x
            soup      = BeautifulSoup(html_text, 'html.parser')
            robots    = Robots.fetch(robots_url)

            # Debug printing
            if(debug):
                print_debug(url, soup, time_now)

            # Add all eligible links in the website to the Queue
            add_links(url, soup, robots)
            visited.add(url)
            domains[main_domain] = time_now
        except:
            pass
        signal.alarm(0)
'''
Create Corpus and initialize the frontier.
Input:
    urls:  List of urls to start
'''
def start(urls):
    # Create corpus directory
    if(not os.path.exists("corpus/")):
        os.makedirs("corpus/")

    # Initialize Queue and set Limit
    for url in urls:
        frontier.put(url_normalize(url))


# ----------------------------------------------------------------------------

'''
Main function for running the program.
Arguments:
    -s Path to seeds
    -n Number of Webpages that should be Crawled
    -d Activate debug mode
'''
if __name__ == '__main__':
    # Remove 1st argument from the
    argumentList = sys.argv[1:]
     
    # Options
    options   = "s:n:d"
    seed_path = ""
    limit     = ""
    debug     = False

    # Parsing arguments
    arguments, values = getopt.getopt(argumentList, options)
    for currentArgument, currentValue in arguments:

        if currentArgument in ("-s"):
            seed_path = currentValue
             
        elif currentArgument in ("-n"):
            limit = int(currentValue)
             
        elif currentArgument in ("-d"):
            debug = True

    if(seed_path == ""):
        raise Exception("No -s argument passed.")

    if(limit == ""):
        raise Exception("No -n argument passed.")

    print(seed_path)
    print(limit)

    seeds = []
    with open(seed_path) as f:
        seeds = f.readlines()

    # Initialize the crawler
    start(seeds)

    # Register the alarm signal with our handler
    signal.signal(signal.SIGALRM, handler)
    mp     = multiprocessing.get_context('spawn')
    # Crawls until requirements are satisfied
    start_time = time.time()
    counter = 0
    while(counter < limit and not frontier.empty()):
        time_passed = time.time() - start_time
        eta         = ((time_passed / counter * limit) - time_passed) if counter else 0
        print("Done",counter,"!\nETA:",int(eta/60),"minutes")
        signal.alarm(5)
        try:
            # Fills buffer
            # buffer = mp.Queue()
            urls = []
            domains_batch = set()
            url_batch     = set()
            pool = multiprocessing.Pool(processes = 50)
            i     = 0
            shift = 0
            while len(url_batch) < NUM_THREADS:
                if(frontier.empty()):
                    break

                # Get first element from Queue
                url         = frontier.get()
                main_domain = urlparse(url).netloc
                if(url in url_batch):
                    continue
                # # Assure that at least 100ms has passed since previous request to domain
                # if(main_domain in domains_batch):
                #     frontier.put(url)
                #     continue

                idx = (i + shift) % NUM_THREADS
                urls.append((url, idx))
                url_batch.add(url)
                i += 1
                # domains_batch.add(main_domain)

            response = pool.starmap(visit, urls)
        except Exception as e:
            print(e)
        signal.alarm(0)
        counter += len(urls)
        shift   += len(urls)

        crawl(response, debug)
        print("End cycle")

    print(len(domains))