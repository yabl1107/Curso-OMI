/* Auto-generated by libinteractive. Do not edit. */
#include "quicksort.h"
#define _XOPEN_SOURCE 600
#if !defined(_WIN32) && !defined(_GNU_SOURCE)
#define _GNU_SOURCE
#endif
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

#if defined(_WIN32)
#if !defined(PRIuS)
#define PRIuS "Iu"
#endif
#else
#if !defined(PRIuS)
#define PRIuS "zu"
#endif
// Windows requires this flag to open files in binary mode using the
// open syscall.
#define O_BINARY 0
#endif

#ifdef __cplusplus
extern "C" {
#endif

struct __stream {
	int fd;
	size_t capacity;
	size_t pos;
	char buffer[4096];
};

static void openstream(struct __stream* stream, const char* path, int flags) {
	stream->fd = open(path, flags | O_BINARY);
	if (stream->fd == -1) {
		perror("open");
		exit(243);
	}
	stream->pos = 0;
	stream->capacity = 0;
}

static void closestream(struct __stream* stream) {
	if (close(stream->fd) == -1) {
		perror("close");
	}
}

static int readfull(struct __stream* stream, void* buf, size_t count, int fatal) {
	ssize_t bytes;
	while (count > 0) {
		if (stream->pos == stream->capacity) {
			stream->pos = 0;
			bytes = read(stream->fd, stream->buffer, sizeof(stream->buffer));
			if (bytes <= 0) {
				if (!fatal) return 0;
				fprintf(stderr, "Incomplete message missing %" PRIuS " bytes\n", count);
				exit(239);
			}
			stream->capacity = (size_t)bytes;
		}

		bytes = (count < stream->capacity - stream->pos) ? count : (stream->capacity - stream->pos);
		memcpy(buf, stream->buffer + stream->pos, bytes);
		stream->pos += bytes;
		count -= bytes;
		buf = bytes + (char*)buf;
	}
	return 1;
}

static void writeflush(struct __stream* stream) {
	const char* to_write = stream->buffer;
	size_t remaining = stream->pos;
	while (remaining > 0) {
		ssize_t bytes = write(stream->fd, to_write, remaining);
		if (bytes <= 0) {
			fprintf(stderr, "Incomplete message missing %" PRIuS " bytes\n", remaining);
			exit(239);
		}
		to_write = bytes + to_write;
		remaining -= bytes;
	}
	stream->pos = 0;
}

static void writefull(struct __stream* stream, const void* buf, size_t count) {
	ssize_t bytes;
	while (count > 0) {
		bytes = (count < sizeof(stream->buffer) - stream->pos) ? count : (sizeof(stream->buffer) - stream->pos);
		memcpy(stream->buffer + stream->pos, buf, bytes);
		stream->pos += bytes;
		buf = bytes + (char*)buf;
		count -= bytes;

		if (stream->pos == sizeof(stream->buffer)) {
			writeflush(stream);
		}
	}
}

static struct __stream __in, __out;

#ifdef __cplusplus
}
#endif

static void __message_loop_Main(int __current_function, int __noreturn) {
	uint32_t __msgid;
	while (readfull(&__in, &__msgid, sizeof(__msgid), 0)) {
		if (__msgid == __current_function) return;
		switch (__msgid) {
			case 0x9cadd6c6u: {
				// Main -> quicksort.HacerParticion
				uint32_t __cookie;
				int HacerParticion_n;
				readfull(&__in, &HacerParticion_n, sizeof(int), 1);
				readfull(&__in, &__cookie, sizeof(__cookie), 1);

				int result =
				HacerParticion(HacerParticion_n);

				writefull(&__out, &__msgid, sizeof(__msgid));
				writefull(&__out, &result, sizeof(result));
				writefull(&__out, &__cookie, sizeof(__cookie));
				writeflush(&__out);
				break;
			}

			default: {
				fprintf(stderr, "Unknown message id 0x%x\n", __msgid);
				exit(241);
			}
		}
	}
	if (__noreturn) {
		exit(0);
	}
	if (__current_function != -1) {
		fprintf(stderr, "Confused about exiting\n");
		exit(242);
	}
}

int ElementoEnPosicion(int i) {
	const uint32_t __msgid = 0x12ffac18u;
	const uint32_t __cookie = 0xfd8a600eu;

	writefull(&__out, &__msgid, sizeof(__msgid));
	writefull(&__out, &i, sizeof(int));
	writefull(&__out, &__cookie, sizeof(__cookie));
	writeflush(&__out);

	__message_loop_Main(__msgid,  1 );
	int __ans = 0;
	readfull(&__in, &__ans, sizeof(__ans), 1);
	uint32_t __cookie_result = 0;
	readfull(&__in, &__cookie_result, sizeof(__cookie_result), 1);

	if (__cookie != __cookie_result) {
		fprintf(stderr, "invalid cookie\n");
		exit(240);
	}
	return __ans;
}

int Intercambiar(int i, int j) {
	const uint32_t __msgid = 0x3f88ff36u;
	const uint32_t __cookie = 0xace3749cu;

	writefull(&__out, &__msgid, sizeof(__msgid));
	writefull(&__out, &i, sizeof(int));
	writefull(&__out, &j, sizeof(int));
	writefull(&__out, &__cookie, sizeof(__cookie));
	writeflush(&__out);

	__message_loop_Main(__msgid,  1 );
	int __ans = 0;
	readfull(&__in, &__ans, sizeof(__ans), 1);
	uint32_t __cookie_result = 0;
	readfull(&__in, &__cookie_result, sizeof(__cookie_result), 1);

	if (__cookie != __cookie_result) {
		fprintf(stderr, "invalid cookie\n");
		exit(240);
	}
	return __ans;
}


int main(int argc, char* argv[]) {
	int retval = 0;

	openstream(&__in, "\\\\.\\pipe\\libinteractive_quicksort_quicksort_in", O_RDONLY);
	openstream(&__out, "\\\\.\\pipe\\libinteractive_quicksort_quicksort_out", O_WRONLY);

	__message_loop_Main(-1, 1);

	closestream(&__in);
	closestream(&__out);

	return retval;
}
