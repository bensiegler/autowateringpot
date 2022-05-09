# Final Project Developer Docs: Auto Watering Pot

This is a final project in the form of an auto houseplant watering system. 
It is currently comprised of a water resevoir, pot, plant, Particle Argon, and 
and various sensors.

This document walks you through how the varying system components fit together & communicate.

### Soil Moisture Sensor Calibration

Although identical, each soil moisture sensor responds slightly differently to identical enviroments. They therefore require calibration to adequately represent the actual soil humitidy/moisture level. This must be done over the course of a few days since an entirely dry soil environment needs to be recorded as well as a fully wet environment. Once this is done the minimum and maximum bounds can be installed. 

### Firmware

On the firmware level, things are relatively simple. Each different sensor has
its library included (if needed. See `project.properties`), and the data is read and stored and a specified interval.

The data can then be directed pretty much anywhere. For this project, I have chosen 
to send it to a Losant Dashboard using JSON.

The pump, instead of being triggered automatically every 15 seconds like sensors,
needs to be remotely accessible. This is achieved using `Particle.function(...)`, creating
a proxy URL for the on-board method. 

#### List of Components/Sensors

Below is a list of the included components: 
- 2x soil moisture sensor
- 1x [horizontal amphibious pump](https://www.sparkfun.com/products/18759)
- 1x DHT environment sensor
- 1x photoresistor
- 1x motor driver
- 1x Li-Ion Battery

### Particle Webhook

The particle webhook is where the data sent from the device is formatted (JSON) & directed to Losant Webhook Endpoint. Basic HTTP Authentication was used to secure the endpoint and SSL is enforced. 

### Losant Workflow

This project/application has two Losant workflows. The first handles the incoming sensor data by sending it on the dashboard/user or creating an event. This workflow is summarized
in the following [image](https://raw.githubusercontent.com/bensiegler/static_images/master/itp348/incoming_data_workflow.png).

The second is simply and endpoint/webhook that allows the creation of events for the dashboard. This is a versatile component of the project as there is a simple framework for
user notification (See DHT Error Handling in final_proj.ino).

### Losant Dashboard 

The dashboard to monitor and contorl the pot can be found [here](https://app.losant.com/dashboards/62759703d9148b4756249d4a). You will be prompted for a password. It is XF99FMncm_JD.@k9Q6Z3PX

### A Note on Timing

For this project I used a RepeatableTimer that automatically calls a function after a certain period of time. It is based on a number of classes in the timers package. 
Notice the importance of inheritence in this package. 