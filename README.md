# AUHack 2022

LEGO case - Improving workspace

## installation
```bash
pip install pyserial
pip install --upgrade firebase-admin
```

## Run the program
First change the serial port in `ser.py` from `ttyACM0` to the desired port, most likely `COM3` or `COM5` if you are on Windows.
It is important to use python3 to run the program, otherwise it will not run. Also remember to connect the Arduino before running the program or it cannot connect.
```bash
python3 main.pr
```

Once the program is running you can then modify the firestore database and see the data being received in the python terminal and sent to the Arduino.