# PeriGuard

## Embedded Linux Peripheral Access and Fault Recovery System

PeriGuard is an individual capstone project developed using C and C++ on Linux.

The project focuses on controlled access to a shared peripheral, device state management, fault detection, and recovery. Since physical hardware is not available, the peripheral is simulated while the Linux device-driver interface and system-level behaviour are implemented as part of the project.

## Project Objective

The objective of PeriGuard is to develop a small embedded Linux system that can:

- Control access to a shared peripheral.
- prevent conflicting access from multiple applications.
- Maintain and monitor the peripheralstate.
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

The  basic architecture of PeriGuard is:

Application
    |
    v
C++ Controller
    |
    v
Linux Character Device Interface
    |
    v
Linux Kernel Module / Device Driver
    |
    v
Simulated Peripheral
    |
    v
State and Fault Management

## Device States

The simulated peripheral follows these main states:

- AVAILABLE
- IN_USE
- FAULT
- RECOVERY
- SAFE_STATE

Normal operation follows:

AVAILABLE -> IN_USE -> AVAILABLE

Afault condition may cause:

IN_USE -> FAULT -> RECOVERY -> AVAILABLE

If recovery fails:

FAULT -> RECOVERY -> SAFE_STATE

## Project Limitation

A physical peripheral is not available for this capstone project. Therefore, the peripheral behaviour is simulated in software while the Linux device-driver and system-programming concepts are demonstrated through the Linux environment.

## Expected Outcome

The final system will demonstrate controlled peripheral access, interaction between user space and kernel space, device-state management, predefined fault handling, recovery, and safe-state behaviour on Linux.

## Project Status 

Development in progress.

