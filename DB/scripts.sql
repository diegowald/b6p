CREATE TABLE "Parametros" (
"Key" TEXT NOT NULL,
"Value" TEXT
);

CREATE TABLE "access" (IDSector INTEGER, Feature TEXT, canRead BOOLEAN, canCreate BOOLEAN, canUpdate BOOLEAN, canDelete BOOLEAN);

CREATE TABLE calendariopersonas (Dia INTEGER, IDEmpleado INTEGER, HoraIngreso INTEGER, HoraEgreso INTEGER, RecordStatus INTEGER);

CREATE TABLE capacidadespersonassector (IDSector INTEGER, IDSubSector INTEGER, IDEmpleado INTEGER, Capacidad REAL, RecordStatus INTEGER);

CREATE TABLE empleados (ID INTEGER PRIMARY KEY, Apellido TEXT, Nombres TEXT, Legajo TEXT, FechaIngreso TEXT, RecordStatus INTEGER);

CREATE TABLE planificaciondia (Dia TEXT, Notas TEXT, IDSupervisor INTEGER, RecordStatus INTEGER);

CREATE TABLE planificaciondias (Dia TEXT, HorasEstimadas INTEGER, RecordStatus INTEGER);

CREATE TABLE planificacionsubsector (IDRecord INTEGER PRIMARY KEY, Dia TEXT, IDSector INTEGER, IDSubsector INTEGER, IDEmpleado INTEGER, HoraInicio INTEGER, HoraFin INTEGER, RecordStatus INTEGER);

CREATE TABLE sectores (ID INTEGER PRIMARY KEY, Nombre TEXT, Descripcion TEXT, RecordStatus INTEGER, showInPlanificaciones BOOLEAN);

CREATE TABLE subsectores (ID INTEGER PRIMARY KEY, IDSector INTEGER, Nombre TEXT, Descripcion TEXT, RecordStatus INTEGER);

