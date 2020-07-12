from PyQt5.QtWidgets import QApplication, QWidget, QVBoxLayout, QPushButton
from ArduinoBTConnector import ArduinoBTConnector


class MainGui:

    def __init__(self):
        # Initiate BT connection
        self.arduino_connection = ArduinoBTConnector()

        # Create application
        self.app = QApplication([])
        self.window = QWidget()
        self.layout = QVBoxLayout()
        self.window.setWindowTitle("Potato Controller")

        # Connect button
        self.connect_button = QPushButton("Connect")
        self.connect_button.clicked.connect(self.connect_with_BT)
        self.layout.addWidget(self.connect_button)

        # Fire button
        self.fire_button = QPushButton("Fire")
        self.fire_button.clicked.connect(self.fire)
        self.layout.addWidget(self.fire_button)

        # Add the layout and show everything
        self.window.setLayout(self.layout)
        self.window.show()
        self.app.exec_()

    def connect_with_BT(self):
        self.arduino_connection.connect_to_arduino(port="/dev/tty.HC-06-DevB", nr=9600)

    def fire(self):
        self.arduino_connection.send_string("1")

gui = MainGui()
