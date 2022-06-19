from warcio.archiveiterator import ArchiveIterator
import sys

with open('corpus/' + sys.argv[1] + '.warc.gz', 'rb') as stream:
    for record in ArchiveIterator(stream):
        if record.rec_type == 'response':
            print(record.rec_headers.get_header('WARC-Target-URI'))
