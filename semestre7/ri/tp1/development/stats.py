from warcio.archiveiterator import ArchiveIterator
from urllib.parse import urlparse
from bs4 import BeautifulSoup
import threading
import pickle


mutex_host_names = threading.Lock()
mutex_pages_per_domain = threading.Lock()
mutex_tokens_per_page = threading.Lock()

host_names = set()
pages_per_domain = dict()
tokens_per_page = []

def runner(l, r):
    for file in range(l, r):
        ct = 0
        with open('corpus/' + str(file) + '.warc.gz', 'rb') as stream:
            print("[", l, ",", r, ") ->", file)
            for i, record in enumerate(ArchiveIterator(stream)):
                if record.rec_type == 'response':
                    url = record.rec_headers.get_header('WARC-Target-URI')
                    s = record.content_stream().read()
                    s_content = s.decode('latin-1')
                    hostname = urlparse(url).hostname

                    mutex_host_names.acquire()
                    host_names.add(hostname)
                    mutex_host_names.release()

                    mutex_pages_per_domain.acquire()
                    if hostname not in pages_per_domain.keys():
                        pages_per_domain[hostname] = 0
                    pages_per_domain[hostname] += 1
                    mutex_pages_per_domain.release()

                    soup = BeautifulSoup(s_content, 'html.parser')
                    try:
                        text = soup.body.get_text()
                        tokens = len(text.split())
                    except:
                        tokens = 0

                    mutex_tokens_per_page.acquire()
                    tokens_per_page.append(tokens)
                    mutex_tokens_per_page.release()
                    ct += 1
                    print("ct = ", ct)

threads = []
for i in range(25):
    thread = threading.Thread(target=runner, args=[4*i, 4*(i + 1)])
    threads.append(thread)
    thread.start()

for i in range(25):
    threads[i].join()


print("Number of unique domains: ", len(host_names))

with open('pickles/host_names.pck', 'wb') as file:
    pickle.dump(host_names, file)

with open('pickles/pages_per_domain.pck', 'wb') as file:
    pickle.dump(pages_per_domain, file)

with open('pickles/tokens_per_page.pck', 'wb') as file:
    pickle.dump(tokens_per_page, file)
