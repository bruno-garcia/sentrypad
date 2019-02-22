libsentry.dylib:
	g++ -g -dynamiclib \
		-o libsentry.dylib sentry.cpp crashpad_wrapper.cpp \
		-I ../crashpad-Darwin/include/ -I ../crashpad-Darwin/include/mini_chromium/ \
		-std=c++11 -L../crashpad-Darwin/lib -lclient -lbase -lutil \
		-framework Foundation -framework Security -framework CoreText \
		-framework CoreGraphics -framework IOKit -lbsm \
		-D SENTRY_CRASHPAD
breakpad-mac:
	g++ -g -dynamiclib \
		-o libsentry.dylib sentry.cpp breakpad_wrapper.cpp \
		-I ../breakpad-Darwin/include/ -I ../breakpad-Darwin/include/common/windows/handler \
		-std=c++11 -L../breakpad-Darwin/lib -lbreakpad_client -ldisasm \
		-framework Foundation -framework Security -framework CoreText \
		-framework CoreGraphics -framework IOKit -lbsm \
		-D SENTRY_BREAKPAD \
		-D MAC
example: example.c libsentry.dylib
	gcc -g -o example example.c -L . -lsentry
build-example: example
clean:
	rm -rf example libsentry.dylib completed new pending *.dSYM