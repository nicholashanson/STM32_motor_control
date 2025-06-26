# STM32 Motor Control

<p align="center">
  <img src="STM32_motor_control.bmp" width="600">
</p>

## Description

Motor control project using TDD ( Unity ) with the goal of integrating it into a turntable system.

UART is set up for integration with QEMU.

## Development Workflow

<p align="center">
  <img src="Images/workflow.jpg" width="600">
</p>

1. **Test-Harness Synchronization**: Any changes made by code generated in CubeMX are refected in the
   test-harness, ensuring the test environment is identical to the production environment.
2. **UnityTest**: Unit-test framework well suited to embedded developement.
3. **Qemu**: Qemu provides support for STM32 simulion through several development boards. This allos 
   to test first on-host.
4. **Proteus**: Proteus provides emulation for STM32 MCUs, allowing us to run firmware and do signal
   analysis.
