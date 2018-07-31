APP := amtlib

build:
	@ gcc ${APP}.c -o ${APP}

run: build
	@ mkdir -p finial
	@ ./${APP} | tee modifications.txt

clean:
	@ rm -rf ${APP}
