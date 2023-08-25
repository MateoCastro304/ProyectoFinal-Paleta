# ProyectoFinal-Paleta
El proyecto consiste de dos etapas:
  Lanzapelotas autómatico y programable, el cual se va a manejar desde el celular para cargar planes de entrenamiento o diferentes tipos de golpes.
  Paleta Sensorial que se encargará de juntar y administrar datos para su análisis y posterior feedback de rendimiento del usuario en su entrenamiento
La paleta consta de un acelerómetro, un giroscopio triaxial, un sensor de presion atmosférica y un microcontrolador ESP8266, el cual se encargará de procesar todos los datos en conjunto con un MPU6050, estos estarán comunicados por I2C.
A su vez, también estarán comunicados al microcontrolador del lanzapelotas para poder enviar informacion y recibir ordenes. Esta comunicación será mediante protocolo ESPNOW o, en su defecto, por Wi-Fi.
