# CloudMesh

## Compilation

To compile, run the following commands:
### Provider
`make TYPE=PROVIDER TARGET=server`
### Requestor
`make TYPE=REQUESTER TARGET=client`

## Compilation (Local)

To compile, run the following commands:
### Provider
`make TYPE=PROVIDER TARGET=server LOCAL=LOCAL`
### Requestor
`make TYPE=REQUESTER TARGET=client LOCAL=LOCAL`


Make sure to run `make clean` before compiling locally. This is since the flags are not removed for individual files.

## Execution

To execute, run the following commands:
### Provider
`./server [8080]` (8080 is the default port, optional parameter)

### Requestor
`./client [8080]` (8080 is the default port, optional parameter)
