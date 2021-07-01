
## Red panda team, why does this work with kafka but not repdanda? 

Trying to figure out why none of my apps can talk with redpanda.



## Test instructions

1. Bring up redpanda,
   `docker-compose up -d redpanda`
2. Add topic test
   `docker-compose exec redpanda rpk topic create test`
3. In one terminal bring up C++ listener.
   `docker-compose up developer`
4. In another terminal, produce a message to topic test from python
   `docker-compose exec developer python3 ./scripts/produce.py`


### Info about app,

listener code [here](./apps/main.cpp)
C++ libs used , librdkafka and modern-cpp-kafka.

producer code [here](./scripts/produce.py)





