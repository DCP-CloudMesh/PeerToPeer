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
### Provider
`./provider [8080]` (8080 is the default port, optional parameter)

### Requestor
`./requestor [8080]` (8080 is the default port, optional parameter)

## Clean

To clean, run the following commands:
### Provider
`make clean TARGET=provider`
### Requestor
`make clean TARGET=requester`
