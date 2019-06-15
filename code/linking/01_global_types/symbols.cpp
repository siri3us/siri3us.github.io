// Uninitialized global variable
int x_global_uninit;

// Initialized global variable
int x_global_init = 1;

// Uninitialized global variable with local scope
static int y_global_uninit;

// Initialized global variable with local scope
static int y_global_init = 2;

// Declaration of a global variable
extern int z_global;

int fn_a(int x, int y);

static int fn_b(int x) {
  return x + 1;
}

int fn_c(int x_local) {
  int y_local_uninit;
  int y_local_init = 3;
  x_global_uninit = fn_a(x_local, x_global_init);
  y_local_uninit = fn_a(x_global_uninit, y_local_init);
  y_local_uninit += fn_b(z_global);
  return y_global_uninit + y_local_uninit;
}
