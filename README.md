Continuation of the [5KES megadthread at DIYSolarForum](https://diysolarforum.com/threads/design-review-growatt-spf-5000-es-grid-backup-neutral-bonding.29717/)

Specifically, the code implementation of [design #216](https://diysolarforum.com/threads/design-review-growatt-spf-5000-es-grid-backup-neutral-bonding.29717/post-402492)

### Latest schematic:
<p align="center">
<img src="./assets/schematic.svg" width="800">
</p>

### [Conduit Schedule](https://electricalestimating101.com/wp-content/uploads/2019/06/NEC-Table-C-Combined-Conduit-Types-THHN-XHHW.pdf)
| Conduit | Type                 | Description                                                   |
| :--     | :--                  | :--                                                           |
| 1       | 3/4" EMT or LT       | Growatt AC Input From Service Panel                           |
| 2       | 3/4" EMT or LT       | Growatt AC Output to Inverter Disconnect Service Panel        |
| 3       | 3/4" EMT or LT       | Inverter Disconnect to 240V Loads Panel (Optional)            |
| 4       | 3/4" EMT or LT       | Inverter Disconnect to Logic Switching Enclosure              |
| 5       | 3/4" EMT or 1/2" LT  | Switching Logic Enclosure to 120/240V Loads Panel             |
| 6       | 1/2" EMT or LT       | Switching Logic Enclosure to Autotransformer                  |
| 7       | 1/2" EMT or LT       | NodeMCU GPIO Interrupt (3VDC Logic Level) ATS Dry Contact     |


### High Voltage Conductor Schedule
| Conduit | Conductor | Gauge | Type                           |
| :--     | :--       | :--   | :--                            |
| 1       | 1         | 6     | THHN 90°C                      |
| 1       | 2         | 6     | THHN 90°C                      |
| 1       | 3         | 10    | THHN 90°C                      |
| 1       | 4         | 6     | THHN 90°C                      |
| 1       | 5         | 6     | THHN 90°C                      |
| 2       | 1         | 6     | THHN 90°C                      |
| 2       | 2         | 6     | THHN 90°C                      |
| 2       | 3         | 10    | THHN 90°C                      |
| 2       | 4         | 6     | THHN 90°C                      |
| 2       | 5         | 6     | THHN 90°C                      |
| 3       | 1         | 6     | THHN 90°C                      |
| 3       | 2         | 6     | THHN 90°C                      |
| 3       | 3         | 6     | THHN 90°C                      |
| 4       | 1         | 10    | THHN 90°C                      |
| 4       | 2         | 10    | THHN 90°C                      |
| 4       | 3         | 10    | THHN 90°C                      |
| 4       | 4         | 10    | THHN 90°C                      |
| 4       | 5         | 10    | THHN 90°C                      |
| 4       | 6         | 10    | THHN 90°C                      |
| 5       | 1         | 10    | THHN 90°C                      |
| 5       | 2         | 10    | THHN 90°C                      |
| 5       | 3         | 10    | THHN 90°C                      |
| 5       | 4         | 10    | THHN 90°C                      |
| 6       | 1         | 10    | THHN 90°C                      |
| 6       | 2         | 10    | THHN 90°C                      |
| 6       | 3         | 10    | THHN 90°C                      |
| 6       | 4         | 10    | THHN 90°C                      |
| 6       | 5         | 22    | K-Type Thermocouple Wire       |
| 6       | 6         | 22    | K-Type Thermocouple Wire       |
| 7       | 1         | 28    | Automotive Primary Wire        |
| 7       | 2         | 28    | Automotive Primary Wire        |

### Low Voltage Conductor Schedule

TBD

