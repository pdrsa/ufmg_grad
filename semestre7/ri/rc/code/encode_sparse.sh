python -m pyserini.index.lucene \
  --collection JsonCollection \
  --input ../data/corpus/no_stop_words \
  --index ../data/indexes/sparse_no_stop \
  --generator DefaultLuceneDocumentGenerator \
  --threads 1 \
  --storePositions --storeDocvectors --storeRaw
