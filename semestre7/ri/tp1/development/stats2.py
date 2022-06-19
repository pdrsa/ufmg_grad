from urllib.parse import urlparse
from bs4 import BeautifulSoup
import pickle
import numpy
import matplotlib.pyplot as plt

host_names = set()
pages_per_domain = dict()
tokens_per_page = []

with open('pickles/host_names.pck', 'rb') as file:
    host_names = pickle.load(file)

with open('pickles/pages_per_domain.pck', 'rb') as file:
    pages_per_domain = pickle.load(file)
    visit = []
    for domain in pages_per_domain:
        visit.append(pages_per_domain[domain])

    print("Average number of pages per domain: ", numpy.mean(visit))
    print("Variance of number of pages per domain: ", numpy.var(visit))
    plt.hist(visit, edgecolor='black',bins = 10)
    plt.xlabel('Páginas')
    plt.ylabel('Domínios')
    plt.xlim([0, 10000])
    plt.plot()
    plt.savefig('plot.png')

with open('pickles/tokens_per_page.pck', 'rb') as file:
    tokens_per_page = pickle.load(file)

    print("Average number of tokens per page: ", numpy.mean(tokens_per_page))

print("Number of unique domains: ", len(host_names))

most_visited = ['google.com',
'youtube.com',
'facebook.com',
'twitter.com',
'instagram.com',
'baidu.com',
'wikipedia.org',
'yandex.ru',
'yahoo.com',
'xvideos.com',
'whatsapp.com',
'amazon.com',
'xnxx.com',
'yahoo.co.jp',
'live.com',
'netflix.com',
'pornhub.com',
'tiktok.com',
'reddit.com',
'office.com',
'vk.com',
'linkedin.com',
'zoom.us',
'xhamster.com',
'discord.com',
'twitch.tv',
'docomo.ne.jp',
'naver.com',
'bing.com',
'mail.ru',
'roblox.com',
'bilibili.com',
'microsoftonline.com',
'duckduckgo.com',
'pinterest.com',
'qq.com',
'msn.com',
'news.yahoo.co.jp',
'microsoft.com',
'turbopages.org',
'globo.com',
'google.com.br',
'samsung.com',
'ebay.com',
'accuweather.com',
'fandom.com',
't.me',
'realsrv.com',
'weather.com',
'ok.ru']

visited = 0
for domain in most_visited:
    was_vis = False
    
    for host in host_names:
        if domain in host:
            was_vis = True
            
    if was_vis:
        visited += 1

print("Most famous visitd = ", visited)
