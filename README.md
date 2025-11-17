# Inter-Process Communication (IPC) & System Programming Concepts

| Category | Mechanism/Concept | Description | Key Characteristics |
|----------|-------------------|-------------|---------------------|
| **Process Control** | `fork` | Creates a new process | Duplicates current process, child continues from fork return |
|  | `syslog` | System logging service | Sends log messages to system log daemon (e.g., rsyslog) |
| **Anonymous Pipes** | `pipe` | Creates anonymous pipe | Unidirectional, only between related processes |
| **Named Pipes** | `FIFO` | Creates named pipe | Has filesystem entry, works with unrelated processes |
| **Message Queues** | `msg_queue` | System V message queues | Message linked list, supports message types and priorities |
| **I/O Multiplexing** | `poll` | I/O event monitoring | Monitors multiple file descriptors for events, more efficient than select |
| **Shared Memory** | `shm` | Shared memory segments | Fastest IPC, multiple processes access same memory region |
| **Synchronization** | `semaphore` | Process synchronization | Controls access to shared resources, prevents race conditions |
| **Signals** | `signal` | Asynchronous notifications | Sends async events to processes for simple communication and control |
| **Network Communication** | `socket` | Network sockets | Communication between processes on same or different hosts, supports TCP/UDP |

## Quick Overview

### Process Management
- **fork**: Fundamental system call for process creation
- **syslog**: System logging interface for application logging

### IPC Mechanisms
| Mechanism | Relationship | Communication Type | Speed |
|-----------|--------------|-------------------|-------|
| Anonymous Pipe | Related processes only | Unidirectional | Fast |
| Named Pipe (FIFO) | Unrelated processes | Unidirectional/Bidirectional | Fast |
| Message Queue | Unrelated processes | Message-based | Medium |
| Shared Memory | Unrelated processes | Memory-based | Very Fast |
| Sockets | Any processes | Stream/Datagram | Variable |

### Synchronization & Signaling
- **Semaphores**: Counter-based synchronization
- **Signals**: Async interrupt-like notifications
- **poll**: Efficient I/O event monitoring

### Use Cases
- **Pipes**: Command pipelines, simple data transfer
- **Message Queues**: Structured message passing
- **Shared Memory**: High-performance data sharing
- **Sockets**: Network communication, client-server apps
- **Signals**: Process control, emergency notifications

## Common System Calls
```c
fork(), pipe(), mkfifo(), msgget(), semget(), shmget(), 
poll(), signal(), socket(), bind(), connect()
