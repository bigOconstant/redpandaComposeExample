import os
# Specific imports
from kafka import KafkaProducer
import logging
from json import dumps


def produce(topic,message):
    producer = KafkaProducer(bootstrap_servers="localhost:9092",
                                api_version=(0, 10, 1))
    msg_as_bytes = str.encode(message)
    producer.send(topic, msg_as_bytes)
    producer.flush() #this is needed, isk why
    #logging.warning("Sent message |"+message+ "| on topic:"+topic) #using warning so it will show in socker logs
    return "Sent message |"+message+ "| on topic:"+topic

print("Reading")

alerts = open('data.json', 'r')
while True:
    line = alerts.readline()
    if not line:
        break
    print(produce("test",line.strip()))
alerts.close()