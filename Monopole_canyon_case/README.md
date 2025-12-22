# Gaussian Canyon Simulation with Monopole Source

This case shows acoustic wave propagation in a Gaussian canyon geometry with a monopole source. The simulation is executed with SPECFEM3D Cartesian, using a custom mesh generated with Cubit, already converted to the SPECFEM3d format and stored in the `MESH/` directory.

---

## 🔧 How to Run the Case

To run the simulation, simply execute:

```bash
./run_this_case.sh
```

This script performs the following steps:

---

### 1. Decompose the Mesh

```bash
./xdecompose_mesh $NPROC ./MESH/ $BASEMPIDIR
```

- Decomposes the external mesh found in the `MESH/` folder.
- `$NPROC` is the number of processors used.
- `$BASEMPIDIR` is the base directory used by MPI for output data.

### 2. Generate the Databases

```bash
mpirun -np $NPROC ./xgenerate_databases
```

- Creates the required databases for the simulation.

### 3. Run the Simulation

```bash
mpirun -np $NPROC ./xspecfem3D
```

- Runs the simulation.
---

### 📂 Case Configuration (Folder: `DATA/`)

The `DATA/` folder contains all configuration files used to define the simulation setup:

 ➤ `CMTSOLUTION`

- Describes the **seismic source**.
- Configured as a **monopole** source.
- Uses an external file containing a **Ricker wavelet** as the source time function.
- The wavelet can be customized by modifying the corresponding input file.

 ➤ `Par_file`

- Main configuration file of the simulation.
- Defines:
  - Number of processors
  - Time stepping (time step size, number of steps)
  - Output settings (e.g., seismograms, field snapshots)
  - Physical and numerical model parameters

 ➤ `STATIONS`

- Lists the receivers where wavefields will be recorded.
- Recorded quantities can include displacement, velocity, acceleration and pressure.

---

### 📌 Notes

- SPECFEM3D was founded by Dimitri Komatitsch and Jeroen Tromp, and is now being developed by a large, collaborative, and inclusive community. A complete list of authors can be found at (https://specfem3d.readthedocs.io/en/latest/authors/)
- SPECFEM3D is part of the software that is hosted by the Computational Infrastructure for Geodynamics (CIG). It is available on the CIG website [here (SPECFEM3D)](https://geodynamics.org/resources/specfem3dcartesian)
- Source code and documentation:
  - 📁 GitHub Repository: https://github.com/SPECFEM/specfem3d
  - 📚 User Guide: https://specfem3d.readthedocs.io/ 

---

