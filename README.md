# KERNEL FOR ICPS

Questo kernel è stato creato con lo scopo di dimostrare l'impiego pratico dell'ICPS. Originariamente, l'ICPS è stato sviluppato in Python, ma durante la progettazione del kernel si è rivelato sconveniente utilizzare un linguaggio di alto livello. Pertanto, il programma è stato riproposto utilizzando Rust.

## Requirements

Per utilizzare questo kernel, sono necessari i seguenti strumenti:

- **Virtualizzatore QEMU**:  
  ```bash
  sudo apt install qemu-system
  ```
- **Make**:
  ```
  sudo apt install make
  ```
- **nasm**:
  ```
  sudo apt install nasm
  ```
- **cross compiler**:
  il tutorial per installarlo puoi trovarle al seguente link https://wiki.osdev.org/GCC_Cross-Compiler

## Informazioni sull'OS

Fino ad ora, questo sistema operativo ha implementato le prime fasi di un normale OS:

### Real Mode
- **Descrizione**: Istruzioni a 16 bit del boot che vengono eseguite direttamente dalla ROM alla CPU.

### Protected Mode
- **Descrizione**: Il bootloader imposta la GDT (Global Descriptor Table) e la carica.  
- **Dettagli**: In questo modo, stabiliamo che i segmenti sono a 4 byte (sono quindi consentite operazioni con i registri a 32 bit).  
- **Funzionamento**: Dopo aver configurato la GDT, il bootloader carica il kernel dal disco nella RAM e esegue un salto (Jump) all'entry point del kernel (`kernel.asm`).

### Text Mode
- **Descrizione**: Quando si entra nella chiamata `kernel_main` del file `kernel.c`, il sistema si trova in fase di Text Mode.

### IDT (Interrupt Descriptor Table)
- **Descrizione**: Sono stati implementati i principali tipi di interrupt.  
- **Dettagli**: La tabella degli interrupt è stata caricata in RAM per gestire le richieste di interrupt in modo efficiente.

## Prossimi Passi

Attualmente, il sistema operativo è in fase di sviluppo e mancano alcuni componenti chiave per completare le funzionalità principali. Ecco i prossimi obiettivi:

### Implementazione del File System
- **Descrizione**: Prima di procedere con l'integrazione della Shell, è necessario completare lo sviluppo del file system.  
- **Dettagli**: Il file system permetterà la gestione di file e directory, fornendo una struttura organizzata per memorizzare e recuperare dati.

### Integrazione della Shell
- **Descrizione**: Una volta completato il file system, verrà implementata l'entry point della Shell all'interno del kernel.  
- **Dettagli**: La Shell fornirà un'interfaccia utente per interagire con il sistema operativo, eseguendo comandi e gestendo le operazioni di base.

### Ottimizzazioni e Debug
- **Descrizione**: Dopo l'implementazione delle funzionalità principali, il focus si sposterà sull'ottimizzazione del codice e sul debugging.  
- **Dettagli**: Verranno risolti eventuali bug e migliorate le prestazioni del sistema operativo.
