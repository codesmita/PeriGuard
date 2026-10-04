# PeriGuard

## Embedded Linux Peripheral Access and Fault Recovery System

PeriGuard is an individual capstone project developed using C and C++ on Linux.

The project focuses on controlled access to a shared peripheral, device state management, fault detection, and recovery. Since physical hardware is not available, the peripheral is simulated while the Linux device-driver interface and system-level behaviour are implemented as part of the project.

## Project Objective

The objective of PeriGuard is to develop a small embedded Linux system that can:

- Control access to a shared peripheral.
- Prevent conflicting access from multiple applications.
- Maintain and monitor the peripheral state.
- Detect predefined device faults.
- Perform controlled recovery.
- Move the device to a safe state when recovery is unsuccessful.
- Demonstrate interaction between user-space software and a Linux character device driver.

## Technologies

- C
- C++
- Linux
- Linux Character Device Driver
- Linux Kernel Module
- POSIX/System Programming concepts
- GNU Make
- GCC/G++
- Git and GitHub

## Project Scope

The project includes:

- A C++ user-space controller.
- A Linux character device driver written in C.
- Controlled access to a simulated shared peripheral.
- Device state management.
- Synchronization between access requests.
- Fault detection and handling.
- Recovery and safe-state management.
- Logging and testing.
- Git-based project management and documentation.

## System Architecture

The basic architecture of PeriGuard is:

Application --> C++ Controller -->  Linux Character Device Interface --> Linux Kernel Module / Device Driver --> Simulated Peripheral --> State and Fault Management

## Device States

The simulated peripheral follows these main states:

- AVAILABLE
- IN_USE
- FAULT
- RECOVERY
- SAFE_STATE

Normal operation follows:
AVAILABLE → IN_USE → AVAILABLE

A fault condition may cause:
IN_USE → FAULT → RECOVERY → AVAILABLE

If recovery is unsuccessful, the defined fallback state is:
FAULT → RECOVERY → SAFE_STATE


## Build and Run

PeriGuard is developed and tested on Ubuntu Linux. 
The following steps explain how to build the Linux character device driver, load it into the kernel, verify the device, build the user-space controller, run the controller, and remove the driver after testing.

### 1. Build the Linux Character Device Driver

The PeriGuard driver is compiled as a Linux kernel module using the Linux kernel build system. From the project root, run:

```bash
make -C /lib/modules/$(uname -r)/build M=$HOME/PeriGuard/driver modules
```

This command compiles the PeriGuard character device driver and generates the `periguard_driver.ko` kernel module.

### 2. Load the Driver into the Linux Kernel

After building the driver, load the compiled kernel module into the running Linux kernel:

```bash
sudo insmod driver/src/periguard_driver.ko
```

The `insmod` command inserts the PeriGuard kernel module into the running kernel. `sudo` is required because loading a kernel module is a privileged operation.

### 3. Verify the Character Device

After loading the driver, verify that the PeriGuard character device has been created:

```bash
ls -l /dev/periguard
```

This command checks the `/dev` directory for the PeriGuard device file. The `/dev/periguard` interface is used by the user-space controller to communicate with the kernel driver.

### 4. Build the User-Space Controller

The C++ controller is built separately from the Linux kernel driver. From the project root, enter the user-space directory:

```bash
cd user-space
```

The `cd` command changes the current directory to the location containing the user-space source files and Makefile.

Build the controller using the provided Makefile:

```bash
make
```

The `make` command compiles the C++ source files and generates the PeriGuard controller executable.

### 5. Run the PeriGuard Controller

After building the controller, run the executable:

```bash
sudo ./controller/periguard
```

This starts the PeriGuard user-space controller. The controller communicates with `/dev/periguard`, sends requests to the Linux character device driver, and displays the resulting access and device-state information.

### 6. Remove the Driver

After completing the tests, return to the project root:

```bash
cd ..
```

The `cd ..` command moves from the `user-space` directory back to the main PeriGuard project directory.

Unload the PeriGuard kernel module:

```bash
sudo rmmod periguard_driver
```

The `rmmod` command removes the PeriGuard driver from the running Linux kernel.

## Test Scenarios

The following test scenarios were used to verify the main functionality of PeriGuard:

| Test Scenario | Expected Result |
|---|---|
| Check device status | Device reports `AVAILABLE` |
| First access request | Access is granted |
| Second access request while the device is in use | Access is denied |
| Release the device | Device returns to `AVAILABLE` |
| Recovery request | Recovery is performed and the device returns to `AVAILABLE` |
| User-space controller communication | Controller successfully communicates with the character device |



## Project Limitation

A physical peripheral is not available for this capstone project. Therefore, the peripheral behaviour is simulated in software while the Linux device-driver and system-programming concepts are demonstrated through the Linux environment.

## Expected Outcome

The final system will demonstrate controlled peripheral access, interaction between user space and kernel space, device-state management, predefined fault handling, recovery, and safe-state behaviour on Linux.

## Project Status 

Completed prototype.

The project was implemented and tested on Ubuntu Linux using a simulated peripheral and Linux character device driver.
