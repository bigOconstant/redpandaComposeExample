#!/bin/bash
echo "Starting redpanda"


rpk redpanda start --smp '1' --reserve-memory 0M --overprovisioned --node-id '0' --kafka-addr PLAINTEXT://0.0.0.0:29092,OUTSIDE://0.0.0.0:9092 --advertise-kafka-addr PLAINTEXT://redpanda:29092,OUTSIDE://localhost:9092 &

echo "creating topic test after one second"
sleep 5
echo "about to create topic"

rpk topic create test;

sleep infinity
