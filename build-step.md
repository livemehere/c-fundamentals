# build step of c file 

```mermaid
flowchart TD 
    main.c --preprocessing--> main.i
    main.i --compilation--> main.s
    main.s --assembly--> main.o
    main.o --linking--> main
```
