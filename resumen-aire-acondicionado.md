# Capturas IR confirmadas - Proyecto control remoto universal

Receptor usado: VS1838B (componente pelado, 3 patas)
Pinout confirmado por prueba real (mirando la cara plana/lente):
- Pata izquierda: OUT
- Pata del medio: GND
- Pata derecha: VCC
(Conectado a Arduino: GND -> GND, VCC -> 5V, OUT -> pin 2)

Librería usada para captura: IRremote (shirriff/Arduino-IRremote) v4.x
Buffer ampliado con: #define RAW_BUFFER_LENGTH 750 (antes del include)

---

## 1. TV TCL - Boton Power

Protocolo: PulseDistance (generico, no es un protocolo de marca con nombre)
Raw-Data: 0xAB054F
Bits: 24
Orden: LSB first

Confirmado estable en 4 capturas distintas, codigo identico en todas.

---

## 2. Barra de sonido - Boton Power

Protocolo: NEC (protocolo estandar, totalmente soportado)
Address: 0x0
Command: 0x45
Raw-Data: 0xBA45FF00
Bits: 32

Confirmado estable en 4 capturas distintas, codigo identico en todas.
Al ser NEC estandar, se puede reenviar facil con sendNEC(address, command, repeats).

---

## 3. Aire Acondicionado Philips - Boton Power

Protocolo: UNKNOWN (no reconocido por nombre, requiere reenvio en formato RAW)
Manda 2 paquetes seguidos por cada pulsacion de Power:

### Paquete 1 (100 bits, Hash=0x5E7E4778)

```
rawIRTimings[200]:
-2537600
+4400,-4300
+600,-1550 +550,-500 +550,-1600 +550,-1600
+550,-500 +550,-500 +550,-1600 +550,-500
+550,-500 +550,-1650 +500,-500 +550,-550
+550,-1600 +500,-1600 +550,-500 +550,-1600
+550,-500 +550,-1600 +550,-1600 +550,-1600
+500,-1600 +550,-500 +550,-1600 +550,-1600
+500,-1600 +550,-500 +550,-550 +550,-500
+550,-500 +550,-1600 +550,-500 +550,-550
+550,-1550 +550,-1600 +550,-1550 +600,-500
+550,-500 +550,-500 +550,-550 +550,-500
+550,-500 +550,-550 +550,-500 +550,-1600
+550,-1550 +550,-1600 +550,-1600 +550,-1550
+550,-5150 +4400,-4300 +550,-1600 +550,-500
+550,-1600 +550,-1550 +600,-500 +550,-500
+550,-1600 +550,-500 +550,-500 +550,-1600
+550,-500 +550,-550 +550,-1550 +550,-1600
+550,-500 +550,-1600 +550,-500 +550,-1600
+550,-1550 +550,-1600 +550,-1600 +550,-500
+550,-1600 +500,-1600 +550,-1600 +550,-500
+550,-550 +500,-550 +500,-550 +550,-1600
+500,-550 +550,-500 +550,-1600 +550,-1600
+500,-1600 +550,-550 +500,-550 +550,-500
+550,-550 +500,-550 +550,-500 +550,-550
+500,-550 +550,-1600 +500,-1600 +550,-1600
+500,-1650 +500,-1600 +550
```
Duration=177150us

### Paquete 2 (150 bits, Hash=0x625E4116)

```
rawIRTimings[300]:
-2596150
+4400,-4300
+550,-1600 +550,-500 +550,-1600 +550,-1600
+550,-500 +550,-500 +550,-1600 +550,-500
+550,-500 +550,-1600 +550,-500 +550,-550
+550,-1600 +500,-1600 +550,-500 +550,-1600
+550,-1600 +550,-500 +550,-1600 +550,-1600
+500,-1600 +550,-1600 +500,-1600 +550,-1600
+550,-500 +550,-1600 +550,-500 +550,-500
+550,-550 +550,-500 +550,-500 +550,-550
+550,-1550 +550,-550 +550,-500 +550,-1550
+600,-1550 +550,-1600 +550,-500 +550,-500
+550,-550 +550,-1550 +550,-1600 +550,-500
+550,-550 +550,-500 +550,-1600 +550,-1550
+550,-5150 +4400,-4300 +550,-1600 +550,-500
+550,-1600 +550,-1600 +550,-500 +550,-500
+550,-1600 +550,-500 +550,-500 +550,-1600
+550,-500 +550,-550 +500,-1600 +550,-1600
+550,-500 +550,-1600 +500,-1650 +550,-500
+500,-1600 +550,-1600 +550,-1600 +500,-1600
+550,-1600 +550,-1600 +500,-550 +550,-1600
+500,-550 +550,-500 +550,-550 +500,-550
+500,-550 +550,-550 +500,-1600 +550,-500
+550,-550 +500,-1600 +550,-1600 +550,-1600
+500,-550 +550,-500 +550,-550 +500,-1600
+550,-1600 +550,-500 +550,-550 +500,-550
+500,-1650 +500,-1600 +550,-5150 +4350,-4350
+550,-1600 +500,-1600 +550,-550 +500,-1600
+550,-550 +500,-1600 +550,-550 +500,-1600
+550,-550 +500,-1600 +550,-1600 +550,-500
+550,-550 +500,-1600 +550,-1600 +500,-550
+550,-500 +550,-550 +500,-550 +550,-500
+550,-550 +500,-550 +550,-500 +550,-550
+500,-550 +550,-500 +550,-550 +500,-550
+550,-500 +550,-550 +500,-550 +550,-500
+550,-550 +500,-550 +500,-550 +550,-550
+500,-550 +500,-550 +550,-550 +500,-550
+500,-550 +550,-500 +550,-1600 +550,-1600
+500,-1600 +550,-550 +500,-1600 +550,-1600
+500
```
Duration=257600us

NOTA IMPORTANTE: estos arrays estan en microsegundos, formato "mark,space" alternado
(el signo + es pulso encendido/mark, el signo - es espacio apagado/space).
Para reenviar con IRremote, hay que convertir esto a un array de uint16_t sin signos
(todos los valores en positivo) y usar IrSender.sendRaw(array, length, 38).

Confirmado estable en 4 capturas distintas, ambos paquetes practicamente
identicos en cada repeticion (variaciones de +-50us, normal jitter de timing).

---

## 4. Lampara Sunset Light - Boton Power

PENDIENTE DE CAPTURAR