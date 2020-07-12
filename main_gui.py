from PyQt5.QtWidgets import QApplication, QWidget, QVBoxLayout, QPushButton, QLabel
from ArduinoBTConnector import ArduinoBTConnector


class MainGui:

    def __init__(self):

        # Boolean for being allowed to fire or not
        self.allowed_to_fire = False

        # Initiate BT connection
        self.arduino_connection = ArduinoBTConnector()

        # Create application
        self.app = QApplication([])
        self.window = QWidget()
        self.layout = QVBoxLayout()
        self.window.setWindowTitle("Potato Controller")
        self.window.setFixedSize(200, 100)

        # Info label
        self.info_str = QLabel()
        self.info_str.setText("Not connected")
        self.layout.addWidget(self.info_str)

        # Connect button
        self.connect_button = QPushButton("Connect")
        self.connect_button.clicked.connect(self.connect_with_BT)
        self.layout.addWidget(self.connect_button)

        # Fire button
        self.fire_button = QPushButton("Fire")
        self.fire_button.clicked.connect(self.fire)
        self.fire_button.setEnabled(self.allowed_to_fire)
        self.layout.addWidget(self.fire_button)

        # Add the layout and show everything
        self.window.setLayout(self.layout)
        self.window.show()
        self.app.exec_()

    def connect_with_BT(self):
        if self.arduino_connection.connect_to_arduino(port="/dev/tty.HC-05-DevB", nr=9600):
            self.allowed_to_fire = True
            self.fire_button.setEnabled(self.allowed_to_fire)
            self.info_str.setText("Connected!")
        self.window.repaint()

    def fire(self):
        self.arduino_connection.send_string("123")
        self.info_str.setText("Connected!")
        self.window.repaint()

gui = MainGui()
