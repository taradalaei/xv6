//new c file for testing our new systemcall
#include "kernel/types.h"
#include "user/user.h"

int main() {
  //calling new systemcall
  trigger();
  exit(0);
}
