stubs:
	[ -f "identity_pb2.py" ] || python -m grpc_tools.protoc -I. --python_out=. --pyi_out=. --grpc_python_out=. identity.proto
	[ -f "pairs_pb2.py" ] || python -m grpc_tools.protoc -I. --python_out=. --pyi_out=. --grpc_python_out=. pairs.proto
run_serv_ident: stubs
	python3 svc_ident.py $(arg1) $(arg2)
run_cli_ident: stubs
	python3 cln_ident.py $(arg1)
run_serv_pares: stubs
	python3 svc_pares.py $(arg1) $(arg2)
run_cli_pares: stubs
	python3 cln_pares.py $(arg1) $(arg2)
clean:
	rm *pb2*
	rm -rf __pycache__