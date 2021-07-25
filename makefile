all: MSOCK CHATAPP
	for dependency in $^; do\
		echo "making $$dependency";\
		make -C $$dependency;\
	done
