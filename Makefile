CC = gcc
CFLAGS = -ICore/Inc -ITest/Inc -IUnity -Wall -Wextra -std=c99

SRC = Core/Src/pwm_control.c Core/Src/motor_control.c Unity/unity.c Test/test_host.c Test/Src/mock_pwm.c Test/Src/test_motor_control.c
OUT = test_pwm

all: $(OUT)

$(OUT): $(SRC)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f $(OUT)
