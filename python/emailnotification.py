#! /usr/bin/python

import socket
import fcntl
import struct

from email.header import Header
from email.mime.text import MIMEText
from getpass import getpass
from smtplib import SMTP_SSL

def get_ip_addr(ifname) :
    s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM);
    return socket.inet_ntoa(fcntl.ioctl(s.fileno(), 0x8915, struct.pack('256s', ifname[:15]))[20:24]);

print "IP Address: ",  get_ip_addr('wlan0');
print "Sending email..."

login, password = "kong.kenny@gmail.com", getpass('Gmail password: ');

msg = MIMEText(get_ip_addr("wlan0"));
msg['Subject'] = Header("My Raspberry Pi IP", "utf-8");
msg['From'] = login;
msg['To'] = login;

s = SMTP_SSL("smtp.gmail.com", 465, timeout = 10);
s.set_debuglevel(0);

try :
    s.login(login, password);
    s.sendmail(msg['From'], msg['To'], msg.as_string());
finally :
    s.quit();
