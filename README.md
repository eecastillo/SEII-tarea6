# SEII-tarea6
# Alejandro Gudiño Gallegos, Eduardo Ethandrake Castillo Pulido
# Descripcion General
Para la elaboracion de esta tarea si utilizo como base el UART con FreeRTOS que proporciono el profesor, esto es porque se quiere que el diseño de ese controlador sea inspirado en la UART. Para poder implementar el i2c con FreeRTOS se usa el driver del SDK llamado i2c, esto para que el driver a realizar sea non-blocking y thread safe.
# BMI160 driver
Para el controlador de BMI160 se usa por medio de comunicacion I2C. Lo primero que se hace es configurar el giroscopio y acelerometro en modo normal. Lo primero que se hace es tener una task que inicilaiza el BMI160, en esta misma task se crea otra task que va a tomar las muestras periodicamente. Al terminar de configurar y crear la nueva task, la task de inicializacion se suspende. La tarea de tomar los datos lo que hace es, cada determinado tiempo, leer los datos que se almacenan en el BMI160. Estos datos se obtienen y luego se presentan en la consola. 
