# CloudMesh

## Compilation

To compile both **PROVIDER** and **REQUESTER**, run the following commands:
`cmake -DLOCAL=0 .`
`cmake --build .`

## Compilation (Local)

To compile both **PROVIDER** and **REQUESTER** locally, run the following commands:
`cmake -DLOCAL=1 .`
`cmake --build .`

## Execution

To execute, run the following commands:
### Bootstrap
`./bin/bootstrap` (8080 is reserved for bootstrap port so peers know where to connect)

### Provider
`./bin/provider [8080]` (8080 is the default port, optional parameter)

### Requester
`./bin/requester [8080 [r | c]]`\
`8080` is the default port, optional parameter\
`r` is an optional parameter to request to receive the result of the computation
`c` is an optional parameter to request to provide the computation
## Clean

To clean, run the following commands:
`make clean`
