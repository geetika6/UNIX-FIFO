# UNIX-FIFO
To implement client server application using FIFO
this has fifo implementation

To create client server implementation for single client and then multiple clients to facilitate that there is message properly going from all clients to server , the data struct being sent can have a pid field to distinguish the particular client from which data is coming and has to go after processing
                _____________
_______         |           |     Pxfifo  ________
|     | Reqfifo |           |------------>|       |
|Rq1  |---^----->| Server   |             |   Px  |
|_____|<--|-----|           |   Resfifo   |       |
 ______   | Cli_|Fifo_n     |<------------|_______|
|     |<--|-----|           |
| Rq2 |   |     |           |
|     |---|     |           |
|_____|   |     |___________|
          |
        --|
