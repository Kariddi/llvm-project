// RUN: %clang -fintegrated-cc1 -c -### %s 2>&1 | FileCheck %s --check-prefix=YES
// RUN: %clang -fno-integrated-cc1 -c -### %s 2>&1 | FileCheck %s --check-prefix=NO

// RUN: %clang -fintegrated-cc1 -fno-integrated-cc1 -c -### %s 2>&1 \
// RUN:     | FileCheck %s --check-prefix=NO
// RUN: %clang -fno-integrated-cc1 -fintegrated-cc1 -c -### %s 2>&1 \
// RUN:     | FileCheck %s --check-prefix=YES

// RUN: %clang_cl -fintegrated-cc1 -c -### -- %s 2>&1 \
// RUN:     | FileCheck %s --check-prefix=YES
// RUN: %clang_cl -fno-integrated-cc1 -c -### -- %s 2>&1 \
// RUN:     | FileCheck %s --check-prefix=NO

// RUN: env CCC_OVERRIDE_OPTIONS=+-fintegrated-cc1 \
// RUN:     %clang -fintegrated-cc1 -c -### %s 2>&1 \
// RUN:     | FileCheck %s --check-prefix=YES
// RUN: env CCC_OVERRIDE_OPTIONS=+-fno-integrated-cc1 \
// RUN:     %clang -fintegrated-cc1 -c -### %s 2>&1 \
// RUN:     | FileCheck %s --check-prefix=NO

// YES: (in-process)
// NO-NOT: (in-process)

// The following tests ensure that only one integrated-cc1 is executed.

// Only one TU, one job, thus integrated-cc1 is enabled.
// RUN: %clang -fintegrated-cc1 -c %s -### 2>&1 | FileCheck %s --check-prefix=YES

// Only one TU, but we're linking, two jobs, thus integrated-cc1 is disabled.
// RUN: %clang -fintegrated-cc1 %s -### 2>&1 | FileCheck %s --check-prefix=NO

// RUN: echo 'int main() { return f() + g(); }' > %t1.cpp
// RUN: echo 'int f() { return 1; }' > %t2.cpp
// RUN: echo 'int g() { return 2; }' > %t3.cpp

// Three jobs, thus integrated-cc1 is disabled.
// RUN: %clang -fintegrated-cc1 -c %t1.cpp %t2.cpp %t3.cpp -### 2>&1 | FileCheck %s --check-prefix=NO
