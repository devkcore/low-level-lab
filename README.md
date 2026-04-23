# low-level-lab 🐧

> "The kernel is not a black box; it's just memory that hasn't been mapped yet."

Minimalistic research playground for low-level Linux internals, binary structures, and memory analysis.

---

### 🔬 Focus Areas

* **Binary Analysis** Inspecting ELF headers, segments, and binary layout at the byte level.
* **Memory Forensics** Exploring `/proc`, `/proc/kcore`, and raw process memory representations.
* **Kernel Internals** Studying syscall boundaries, memory mapping, and kernel-space interactions.

---

### 🛠️ Tools & Experiments

* `tools/elf_check.c`  
    Minimal ELF header validator using raw magic byte inspection (`0x7F 'E' 'L' 'F'`).
* `scripts/mem_dump.sh`  
    Experimental interface for inspecting process memory via `/proc`.

---

### ⚙️ Usage

**Compile and run:**

```bash
gcc -o elf_check tools/elf_check.c
./elf_check /bin/ls
