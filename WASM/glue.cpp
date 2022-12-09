
#include <emscripten.h>

EM_JS_DEPS(webidl_binder, "$intArrayFromString");

extern "C" {

// Not using size_t for array indices as the values used by the javascript code are signed.

EM_JS(void, array_bounds_check_error, (size_t idx, size_t size), {
  throw 'Array index ' + idx + ' out of bounds: [0,' + size + ')';
});

void array_bounds_check(const int array_size, const int array_idx) {
  if (array_idx < 0 || array_idx >= array_size) {
    array_bounds_check_error(array_idx, array_size);
  }
}

// VoidPtr

void EMSCRIPTEN_KEEPALIVE emscripten_bind_VoidPtr___destroy___0(void** self) {
  delete self;
}

// Runner

Runner* EMSCRIPTEN_KEEPALIVE emscripten_bind_Runner_Runner_0() {
  return new Runner();
}

void EMSCRIPTEN_KEEPALIVE emscripten_bind_Runner_addPlayers_0(Runner* self) {
  self->addPlayers();
}

void EMSCRIPTEN_KEEPALIVE emscripten_bind_Runner_start_0(Runner* self) {
  self->start();
}

void EMSCRIPTEN_KEEPALIVE emscripten_bind_Runner___destroy___0(Runner* self) {
  delete self;
}

}

