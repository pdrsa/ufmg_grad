python -m pyserini.encode \
  input   --corpus ../data/corpus/corpus.jsonl \
          --fields title text \  # fields in collection contents
          --delimiter "\n" \
          --shard-id 0 \   # The id of current shard. Default is 0
          --shard-num 1 \  # The total number of shards. Default is 1
  output  --embeddings ../data/indexes/ \
  encoder --encoder castorini/tct_colbert-v2-hnp-msmarco \
          --fields title text \  # fields to encode, they must appear in the input.fields
          --batch 32 \
          --fp16  # if inference with autocast()
