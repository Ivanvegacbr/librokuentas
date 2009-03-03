--
-- PostgreSQL database dump
--

SET client_encoding = 'UTF8';
SET standard_conforming_strings = off;
SET check_function_bodies = false;
SET client_min_messages = warning;
SET escape_string_warning = off;

--
-- Name: SCHEMA public; Type: COMMENT; Schema: -; Owner: postgres
--

COMMENT ON SCHEMA public IS 'Standard public schema';


SET search_path = public, pg_catalog;

SET default_tablespace = '';

SET default_with_oids = false;

--
-- Name: ajustes_conci; Type: TABLE; Schema: public; Owner: pepe; Tablespace: 
--

CREATE TABLE ajustes_conci (
    cuenta character varying(40),
    fecha date,
    debe numeric(14,2),
    haber numeric(14,2),
    concepto character varying(255),
    dif_conciliacion character varying(40) DEFAULT ''::character varying,
    conciliado boolean DEFAULT false
);


ALTER TABLE public.ajustes_conci OWNER TO pepe;

SET default_with_oids = true;

--
-- Name: amortcontable; Type: TABLE; Schema: public; Owner: pepe; Tablespace: 
--

CREATE TABLE amortcontable (
    ejercicio character varying(40) NOT NULL,
    asiento bigint
);


ALTER TABLE public.amortcontable OWNER TO pepe;

--
-- Name: amortfiscalycontable; Type: TABLE; Schema: public; Owner: pepe; Tablespace: 
--

CREATE TABLE amortfiscalycontable (
    ejercicio character varying(40) NOT NULL,
    cuenta_activo character varying(40) NOT NULL,
    codigo_activo character varying(40),
    cuenta_am_acum character varying(40),
    cuenta_gasto character varying(40),
    dotacion_contable numeric(14,2),
    dotacion_fiscal numeric(14,2)
);


ALTER TABLE public.amortfiscalycontable OWNER TO pepe;

--
-- Name: amortpers; Type: TABLE; Schema: public; Owner: pepe; Tablespace: 
--

CREATE TABLE amortpers (
    cuenta character varying(40) NOT NULL,
    ejercicio character varying(40) NOT NULL,
    importe numeric(14,2)
);


ALTER TABLE public.amortpers OWNER TO pepe;

--
-- Name: borrador; Type: TABLE; Schema: public; Owner: pepe; Tablespace: 
--

CREATE TABLE borrador (
    asiento bigint,
    usuario character varying(80),
    cuenta character varying(40),
    concepto character varying(80),
    debe character varying(40),
    haber character varying(40),
    documento character varying(40),
    ctabaseiva character varying(40),
    baseiva character varying(40),
    claveiva character varying(40),
    tipoiva character varying(40),
    tipore character varying(40),
    cuotaiva character varying(40),
    cuentafra character varying(40),
    diafra character varying(40),
    mesfra character varying(40),
    anyofra character varying(40),
    soportado character varying(40),
    ci character varying(40),
    prorrata character varying(40) DEFAULT ''::character varying,
    rectificativa character varying(40) DEFAULT ''::character varying,
    autofactura character varying(40) DEFAULT ''::character varying
);


ALTER TABLE public.borrador OWNER TO pepe;

--
-- Name: cab_as_modelo; Type: TABLE; Schema: public; Owner: pepe; Tablespace: 
--

CREATE TABLE cab_as_modelo (
    asientomodelo character varying NOT NULL,
    fecha character varying
);


ALTER TABLE public.cab_as_modelo OWNER TO pepe;

--
-- Name: cabeceraestados; Type: TABLE; Schema: public; Owner: pepe; Tablespace: 
--

CREATE TABLE cabeceraestados (
    titulo character varying NOT NULL,
    cabecera character varying,
    parte1 character varying,
    parte2 character varying,
    observaciones character varying,
    formulabasepor character varying,
    fechacalculo date,
    ejercicio1 character varying,
    ejercicio2 character varying,
    analitica boolean,
    haycolref boolean,
    colref character varying(80),
    ci character varying(80),
    desglose boolean,
    des_cabecera character varying,
    des_pie character varying,
    estadosmedios boolean,
    valorbasepor1 numeric(14,2),
    valorbasepor2 numeric(14,2),
    diarios character varying(255),
    grafico boolean
);


ALTER TABLE public.cabeceraestados OWNER TO pepe;

--
-- Name: ci; Type: TABLE; Schema: public; Owner: pepe; Tablespace: 
--

CREATE TABLE ci (
    codigo character varying(40) NOT NULL,
    descripcion character varying(80),
    nivel integer NOT NULL
);


ALTER TABLE public.ci OWNER TO pepe;

SET default_with_oids = false;

--
-- Name: ci_amort; Type: TABLE; Schema: public; Owner: pepe; Tablespace: 
--

CREATE TABLE ci_amort (
    cuenta character varying(40) NOT NULL,
    ci character varying(40) NOT NULL,
    asignacion double precision
);


ALTER TABLE public.ci_amort OWNER TO pepe;

SET default_with_oids = true;

--
-- Name: conceptos; Type: TABLE; Schema: public; Owner: pepe; Tablespace: 
--

CREATE TABLE conceptos (
    clave character varying(10) NOT NULL,
    descripcion character varying(80)
);


ALTER TABLE public.conceptos OWNER TO pepe;

--
-- Name: configuracion; Type: TABLE; Schema: public; Owner: pepe; Tablespace: 
--

CREATE TABLE configuracion (
    empresa character varying,
    nif character varying,
    domicilio character varying,
    poblacion character varying,
    cpostal character varying,
    provincia character varying,
    email character varying,
    web character varying,
    anchocuentas integer,
    cuenta_iva_soportado character varying,
    cuenta_iva_repercutido character varying,
    cuenta_ret_irpf character varying,
    cuentasapagar character varying,
    cuentasacobrar character varying,
    clave_iva_defecto character varying,
    clave_gastos character varying,
    clave_ingresos character varying,
    cuenta_pyg character varying,
    prox_asiento bigint,
    prox_pase bigint,
    prox_vencimiento bigint,
    numrel boolean,
    igic boolean,
    analitica boolean,
    version character varying(40),
    bloqsaldosmedios boolean,
    id_registral character varying(255),
    prorrata_iva numeric(5,2) DEFAULT 0,
    prorrata_especial boolean DEFAULT false
);


ALTER TABLE public.configuracion OWNER TO pepe;

SET default_with_oids = false;

--
-- Name: cuenta_ext_conci; Type: TABLE; Schema: public; Owner: pepe; Tablespace: 
--

CREATE TABLE cuenta_ext_conci (
    numero integer NOT NULL,
    cuenta character varying(40),
    fecha date,
    debe numeric(14,2),
    haber numeric(14,2),
    saldo numeric(14,2),
    concepto character varying(255),
    dif_conciliacion character varying(40) DEFAULT ''::character varying,
    conciliado boolean DEFAULT false
);


ALTER TABLE public.cuenta_ext_conci OWNER TO pepe;

--
-- Name: cuenta_ext_conci_numero_seq; Type: SEQUENCE; Schema: public; Owner: pepe
--

CREATE SEQUENCE cuenta_ext_conci_numero_seq
    START WITH 1
    INCREMENT BY 1
    NO MAXVALUE
    NO MINVALUE
    CACHE 1;


ALTER TABLE public.cuenta_ext_conci_numero_seq OWNER TO pepe;

--
-- Name: cuenta_ext_conci_numero_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: pepe
--

ALTER SEQUENCE cuenta_ext_conci_numero_seq OWNED BY cuenta_ext_conci.numero;


--
-- Name: cuenta_ext_conci_numero_seq; Type: SEQUENCE SET; Schema: public; Owner: pepe
--

SELECT pg_catalog.setval('cuenta_ext_conci_numero_seq', 1, false);


SET default_with_oids = true;

--
-- Name: datossubcuenta; Type: TABLE; Schema: public; Owner: pepe; Tablespace: 
--

CREATE TABLE datossubcuenta (
    cuenta character varying(40) NOT NULL,
    razon character varying(80),
    nombrecomercial character varying(80),
    cif character varying(80),
    nifcomunitario character varying(40),
    domicilio character varying(80),
    poblacion character varying(80),
    codigopostal character varying(40),
    provincia character varying(80),
    pais character varying(80),
    tfno character varying(80),
    fax character varying(80),
    email character varying(80),
    observaciones character varying(80),
    ccc character varying(255),
    cuota character varying(40)
);


ALTER TABLE public.datossubcuenta OWNER TO pepe;

--
-- Name: det_as_modelo; Type: TABLE; Schema: public; Owner: pepe; Tablespace: 
--

CREATE TABLE det_as_modelo (
    asientomodelo character varying,
    cuenta character varying,
    concepto character varying,
    expresion character varying,
    d_h character varying,
    ci character varying,
    baseiva character varying,
    cuentafra character varying,
    cuentabaseiva character varying,
    claveiva character varying,
    documento character varying,
    orden integer
);


ALTER TABLE public.det_as_modelo OWNER TO pepe;

--
-- Name: diario; Type: TABLE; Schema: public; Owner: pepe; Tablespace: 
--

CREATE TABLE diario (
    asiento bigint,
    pase bigint NOT NULL,
    fecha date,
    cuenta character varying(40),
    debe numeric(14,2),
    haber numeric(14,2),
    concepto character varying(80),
    documento character varying(40),
    diario character varying(20),
    ci character varying(40),
    usuario character varying(80),
    conciliado boolean DEFAULT false,
    dif_conciliacion character varying(40) DEFAULT ''::character varying
);


ALTER TABLE public.diario OWNER TO pepe;

SET default_with_oids = false;

--
-- Name: diarios; Type: TABLE; Schema: public; Owner: pepe; Tablespace: 
--

CREATE TABLE diarios (
    codigo character varying(40) NOT NULL,
    descripcion character varying(255)
);


ALTER TABLE public.diarios OWNER TO pepe;

--
-- Name: dif_conciliacion; Type: TABLE; Schema: public; Owner: pepe; Tablespace: 
--

CREATE TABLE dif_conciliacion (
    codigo character varying(40) NOT NULL,
    descripcion character varying(80) DEFAULT ''::character varying
);


ALTER TABLE public.dif_conciliacion OWNER TO pepe;

SET default_with_oids = true;

--
-- Name: ejercicios; Type: TABLE; Schema: public; Owner: pepe; Tablespace: 
--

CREATE TABLE ejercicios (
    codigo character varying(40) NOT NULL,
    apertura date,
    cierre date,
    cerrado boolean,
    cerrando boolean,
    primerasiento bigint,
    base_ejercicio character varying(80) DEFAULT ''::character varying,
    base_presupuesto character varying(80) DEFAULT ''::character varying,
    presupuesto_base_cero boolean DEFAULT true,
    incremento numeric(14,4) DEFAULT 0
);


ALTER TABLE public.ejercicios OWNER TO pepe;

--
-- Name: equivalenciasplan; Type: TABLE; Schema: public; Owner: pepe; Tablespace: 
--

CREATE TABLE equivalenciasplan (
    cod character varying(40) NOT NULL,
    equiv character varying(40)
);


ALTER TABLE public.equivalenciasplan OWNER TO pepe;

--
-- Name: estados; Type: TABLE; Schema: public; Owner: pepe; Tablespace: 
--

CREATE TABLE estados (
    titulo character varying(166) NOT NULL,
    apartado character varying,
    parte1 boolean NOT NULL,
    clave character varying,
    nodo character varying(166) NOT NULL,
    formula character varying,
    referencia character varying(80),
    importe1 numeric(14,2),
    importe2 numeric(14,2),
    calculado boolean
);


ALTER TABLE public.estados OWNER TO pepe;

--
-- Name: libroiva; Type: TABLE; Schema: public; Owner: pepe; Tablespace: 
--

CREATE TABLE libroiva (
    pase bigint NOT NULL,
    cta_base_iva character varying(40),
    base_iva numeric(14,2),
    clave_iva character varying(4),
    tipo_iva numeric(5,2),
    tipo_re numeric(5,2),
    cuota_iva numeric(14,2),
    cuenta_fra character varying(40),
    fecha_fra date,
    soportado boolean,
    aib boolean,
    eib boolean,
    prorrata numeric(5,2) DEFAULT 1,
    rectificativa boolean DEFAULT false,
    autofactura boolean DEFAULT false
);


ALTER TABLE public.libroiva OWNER TO pepe;

--
-- Name: nuevoplan; Type: TABLE; Schema: public; Owner: pepe; Tablespace: 
--

CREATE TABLE nuevoplan (
    codigo character varying(40) NOT NULL,
    descripcion character varying
);


ALTER TABLE public.nuevoplan OWNER TO pepe;

SET default_with_oids = false;

--
-- Name: periodos; Type: TABLE; Schema: public; Owner: pepe; Tablespace: 
--

CREATE TABLE periodos (
    ejercicio character varying(40) NOT NULL,
    codigo character varying(40) NOT NULL,
    inicio date,
    fin date
);


ALTER TABLE public.periodos OWNER TO pepe;

SET default_with_oids = true;

--
-- Name: planamortizaciones; Type: TABLE; Schema: public; Owner: pepe; Tablespace: 
--

CREATE TABLE planamortizaciones (
    cuenta_activo character varying(40) NOT NULL,
    fecha_func date,
    codigo_activo character varying(40),
    cuenta_am_acum character varying(40),
    cuenta_gasto character varying(40),
    valor_residual numeric(14,2),
    amort_personalizada boolean,
    coef_amort_contable double precision,
    coef_amort_fiscal double precision,
    amort_fiscal_1ejer boolean
);


ALTER TABLE public.planamortizaciones OWNER TO pepe;

--
-- Name: plancontable; Type: TABLE; Schema: public; Owner: pepe; Tablespace: 
--

CREATE TABLE plancontable (
    codigo character varying(40) NOT NULL,
    descripcion character varying,
    auxiliar boolean DEFAULT false
);


ALTER TABLE public.plancontable OWNER TO pepe;

SET default_with_oids = false;

--
-- Name: presupuesto; Type: TABLE; Schema: public; Owner: pepe; Tablespace: 
--

CREATE TABLE presupuesto (
    ejercicio character varying(40) NOT NULL,
    cuenta character varying(40) NOT NULL,
    ejerciciobase character varying(40) DEFAULT ''::character varying,
    presupuestobase character varying(40) DEFAULT ''::character varying,
    base numeric(14,2) DEFAULT 0,
    base1 numeric(14,2) DEFAULT 0,
    base2 numeric(14,2) DEFAULT 0,
    base3 numeric(14,2) DEFAULT 0,
    base4 numeric(14,2) DEFAULT 0,
    base5 numeric(14,2) DEFAULT 0,
    base6 numeric(14,2) DEFAULT 0,
    base7 numeric(14,2) DEFAULT 0,
    base8 numeric(14,2) DEFAULT 0,
    base9 numeric(14,2) DEFAULT 0,
    base10 numeric(14,2) DEFAULT 0,
    base11 numeric(14,2) DEFAULT 0,
    base12 numeric(14,2) DEFAULT 0,
    base13 numeric(14,2) DEFAULT 0,
    base14 numeric(14,2) DEFAULT 0,
    base15 numeric(14,2) DEFAULT 0,
    presupuesto numeric(14,2) DEFAULT 0,
    presupuesto1 numeric(14,2) DEFAULT 0,
    presupuesto2 numeric(14,2) DEFAULT 0,
    presupuesto3 numeric(14,2) DEFAULT 0,
    presupuesto4 numeric(14,2) DEFAULT 0,
    presupuesto5 numeric(14,2) DEFAULT 0,
    presupuesto6 numeric(14,2) DEFAULT 0,
    presupuesto7 numeric(14,2) DEFAULT 0,
    presupuesto8 numeric(14,2) DEFAULT 0,
    presupuesto9 numeric(14,2) DEFAULT 0,
    presupuesto10 numeric(14,2) DEFAULT 0,
    presupuesto11 numeric(14,2) DEFAULT 0,
    presupuesto12 numeric(14,2) DEFAULT 0,
    presupuesto13 numeric(14,2) DEFAULT 0,
    presupuesto14 numeric(14,2) DEFAULT 0,
    presupuesto15 numeric(14,2) DEFAULT 0
);


ALTER TABLE public.presupuesto OWNER TO pepe;

SET default_with_oids = true;

--
-- Name: saldossubcuenta; Type: TABLE; Schema: public; Owner: pepe; Tablespace: 
--

CREATE TABLE saldossubcuenta (
    codigo character varying(40) NOT NULL,
    saldo numeric(14,2),
    saldomedio1 numeric(14,2),
    saldomedio2 numeric(14,2)
);


ALTER TABLE public.saldossubcuenta OWNER TO pepe;

--
-- Name: tiposiva; Type: TABLE; Schema: public; Owner: pepe; Tablespace: 
--

CREATE TABLE tiposiva (
    clave character varying(4) NOT NULL,
    tipo numeric(5,2),
    re numeric(5,2),
    descripcion character varying(80)
);


ALTER TABLE public.tiposiva OWNER TO pepe;

--
-- Name: var_as_modelo; Type: TABLE; Schema: public; Owner: pepe; Tablespace: 
--

CREATE TABLE var_as_modelo (
    asientomodelo character varying(166) NOT NULL,
    variable character varying(166) NOT NULL,
    tipo character varying,
    descripcion character varying,
    orden integer
);


ALTER TABLE public.var_as_modelo OWNER TO pepe;

--
-- Name: vencimientos; Type: TABLE; Schema: public; Owner: pepe; Tablespace: 
--

CREATE TABLE vencimientos (
    num bigint NOT NULL,
    cta_ordenante character varying(40),
    fecha_operacion date,
    importe numeric(14,2),
    cuenta_tesoreria character varying(40),
    fecha_vencimiento date,
    derecho boolean,
    pendiente boolean,
    anulado boolean,
    pase_diario_operacion bigint,
    pase_diario_vencimiento bigint,
    usuario character varying(80),
    concepto character varying DEFAULT ''::character varying
);


ALTER TABLE public.vencimientos OWNER TO pepe;

--
-- Name: numero; Type: DEFAULT; Schema: public; Owner: pepe
--

ALTER TABLE cuenta_ext_conci ALTER COLUMN numero SET DEFAULT nextval('cuenta_ext_conci_numero_seq'::regclass);


--
-- Data for Name: ajustes_conci; Type: TABLE DATA; Schema: public; Owner: pepe
--

COPY ajustes_conci (cuenta, fecha, debe, haber, concepto, dif_conciliacion, conciliado) FROM stdin;
\.


--
-- Data for Name: amortcontable; Type: TABLE DATA; Schema: public; Owner: pepe
--

COPY amortcontable (ejercicio, asiento) FROM stdin;
2008	37
\.


--
-- Data for Name: amortfiscalycontable; Type: TABLE DATA; Schema: public; Owner: pepe
--

COPY amortfiscalycontable (ejercicio, cuenta_activo, codigo_activo, cuenta_am_acum, cuenta_gasto, dotacion_contable, dotacion_fiscal) FROM stdin;
2008	21700003	PC3	28170003	68100001	106.64	900.00
\.


--
-- Data for Name: amortpers; Type: TABLE DATA; Schema: public; Owner: pepe
--

COPY amortpers (cuenta, ejercicio, importe) FROM stdin;
\.


--
-- Data for Name: borrador; Type: TABLE DATA; Schema: public; Owner: pepe
--

COPY borrador (asiento, usuario, cuenta, concepto, debe, haber, documento, ctabaseiva, baseiva, claveiva, tipoiva, tipore, cuotaiva, cuentafra, diafra, mesfra, anyofra, soportado, ci, prorrata, rectificativa, autofactura) FROM stdin;
\.


--
-- Data for Name: cab_as_modelo; Type: TABLE DATA; Schema: public; Owner: pepe
--

COPY cab_as_modelo (asientomodelo, fecha) FROM stdin;
\.


--
-- Data for Name: cabeceraestados; Type: TABLE DATA; Schema: public; Owner: pepe
--

COPY cabeceraestados (titulo, cabecera, parte1, parte2, observaciones, formulabasepor, fechacalculo, ejercicio1, ejercicio2, analitica, haycolref, colref, ci, desglose, des_cabecera, des_pie, estadosmedios, valorbasepor1, valorbasepor2, diarios, grafico) FROM stdin;
BALANCE PYMES PLAN 2007	BALANCE DE PYMES AL CIERRE DEL EJERCICIO	ACTIVO	PATRIMONIO NETO Y PASIVO			2000-01-01			f	t	Nota		\N	\N	\N	f	0.00	0.00	APERTURA SIN_ASIGNAR REGULARIZACION	\N
CUENTA PÉRDIDAS Y GANANCIAS PYMES PLAN 2007	CUENTA DE PÉRDIDAS Y GANANCIAS PYMES					2000-01-01	2009		f	t	Nota		\N	\N	\N	f	0.00	0.00	APERTURA SIN_ASIGNAR	\N
\.


--
-- Data for Name: ci; Type: TABLE DATA; Schema: public; Owner: pepe
--

COPY ci (codigo, descripcion, nivel) FROM stdin;
\.


--
-- Data for Name: ci_amort; Type: TABLE DATA; Schema: public; Owner: pepe
--

COPY ci_amort (cuenta, ci, asignacion) FROM stdin;
\.


--
-- Data for Name: conceptos; Type: TABLE DATA; Schema: public; Owner: pepe
--

COPY conceptos (clave, descripcion) FROM stdin;
1	Ventas
2	Compra mercaderías
\.


--
-- Data for Name: configuracion; Type: TABLE DATA; Schema: public; Owner: pepe
--

COPY configuracion (empresa, nif, domicilio, poblacion, cpostal, provincia, email, web, anchocuentas, cuenta_iva_soportado, cuenta_iva_repercutido, cuenta_ret_irpf, cuentasapagar, cuentasacobrar, clave_iva_defecto, clave_gastos, clave_ingresos, cuenta_pyg, prox_asiento, prox_pase, prox_vencimiento, numrel, igic, analitica, version, bloqsaldosmedios, id_registral, prorrata_iva, prorrata_especial) FROM stdin;
Empresa de ejemplo								8	472	477		400,401	430,431	GN	6	7	129.0	42	141	13	f	f	f	2.2	f		0.00	f
\.


--
-- Data for Name: cuenta_ext_conci; Type: TABLE DATA; Schema: public; Owner: pepe
--

COPY cuenta_ext_conci (numero, cuenta, fecha, debe, haber, saldo, concepto, dif_conciliacion, conciliado) FROM stdin;
\.


--
-- Data for Name: datossubcuenta; Type: TABLE DATA; Schema: public; Owner: pepe
--

COPY datossubcuenta (cuenta, razon, nombrecomercial, cif, nifcomunitario, domicilio, poblacion, codigopostal, provincia, pais, tfno, fax, email, observaciones, ccc, cuota) FROM stdin;
11200000														\N	\N
\.


--
-- Data for Name: det_as_modelo; Type: TABLE DATA; Schema: public; Owner: pepe
--

COPY det_as_modelo (asientomodelo, cuenta, concepto, expresion, d_h, ci, baseiva, cuentafra, cuentabaseiva, claveiva, documento, orden) FROM stdin;
\.


--
-- Data for Name: diario; Type: TABLE DATA; Schema: public; Owner: pepe
--

COPY diario (asiento, pase, fecha, cuenta, debe, haber, concepto, documento, diario, ci, usuario, conciliado, dif_conciliacion) FROM stdin;
1	1	2008-01-01	10000000	0.00	60000.00	Asiento de apertura		APERTURA		pepe	f	
1	2	2008-01-01	11200000	0.00	7500.00	Asiento de apertura		APERTURA		pepe	f	
1	3	2008-01-01	12900000	0.00	5600.00	Asiento de apertura		APERTURA		pepe	f	
1	4	2008-01-01	21000001	20000.00	0.00	Asiento de apertura		APERTURA		pepe	f	
1	5	2008-01-01	21100001	25000.00	0.00	Asiento de apertura		APERTURA		pepe	f	
1	6	2008-01-01	28110001	0.00	1250.00	Asiento de apertura		APERTURA		pepe	f	
1	7	2008-01-01	21600001	4000.00	0.00	Asiento de apertura		APERTURA		pepe	f	
1	8	2008-01-01	28160001	0.00	2000.00	Asiento de apertura		APERTURA		pepe	f	
1	9	2008-01-01	21700001	1000.00	0.00	Asiento de apertura		APERTURA		pepe	f	
1	10	2008-01-01	28170001	0.00	500.00	Asiento de apertura		APERTURA		pepe	f	
1	11	2008-01-01	21700002	800.00	0.00	Asiento de apertura		APERTURA		pepe	f	
1	12	2008-01-01	28170002	0.00	200.00	Asiento de apertura		APERTURA		pepe	f	
1	13	2008-01-01	30000000	24000.00	0.00	Asiento de apertura		APERTURA		pepe	f	
1	14	2008-01-01	40000001	0.00	2000.00	Asiento de apertura		APERTURA		pepe	f	
1	15	2008-01-01	40000002	0.00	1500.00	Asiento de apertura		APERTURA		pepe	f	
1	16	2008-01-01	43000001	500.00	0.00	Asiento de apertura		APERTURA		pepe	f	
1	17	2008-01-01	43000002	400.00	0.00	Asiento de apertura		APERTURA		pepe	f	
1	18	2008-01-01	47500000	0.00	850.00	Asiento de apertura		APERTURA		pepe	f	
1	19	2008-01-01	47520000	0.00	300.00	Asiento de apertura		APERTURA		pepe	f	
1	20	2008-01-01	57000000	6000.00	0.00	Asiento de apertura		APERTURA		pepe	f	
2	21	2008-01-08	47500000	850.00	0.00	Pago IVA 4t 2007				pepe	f	
2	22	2008-01-08	57000000	0.00	850.00	Pago IVA 4t 2007				pepe	f	
3	23	2008-01-10	43000001	0.00	500.00	Vto. Cliente A de 01.08.2008			\N	pepe	f	
3	24	2008-01-10	57000000	500.00	0.00	Vto. Cliente A de 01.08.2008			\N	pepe	f	
4	25	2008-01-10	43000001	116.00	0.00	Ventas a Cliente A				pepe	f	
4	26	2008-01-10	70000000	0.00	100.00	Ventas a Cliente A				pepe	f	
4	27	2008-01-10	47700000	0.00	16.00	Ventas a Cliente A				pepe	f	
5	28	2008-01-10	43000001	0.00	116.00	Vto. Cliente A de 10.01.2008			\N	pepe	f	
5	29	2008-01-10	57000000	116.00	0.00	Vto. Cliente A de 10.01.2008			\N	pepe	f	
6	30	2008-01-16	43000002	0.00	400.00	Vto. Cliente B de 01.08.2008			\N	pepe	f	
6	31	2008-01-16	57000000	400.00	0.00	Vto. Cliente B de 01.08.2008			\N	pepe	f	
7	32	2008-01-20	40000001	1500.00	0.00	Vto. Proveedor A de 01.08.2008			\N	pepe	f	
7	33	2008-01-20	57000000	0.00	1500.00	Vto. Proveedor A de 01.08.2008			\N	pepe	f	
8	34	2008-02-05	40000002	1500.00	0.00	Vto. Proveedor B de 01.08.2008			\N	pepe	f	
8	35	2008-02-05	57000000	0.00	1500.00	Vto. Proveedor B de 01.08.2008			\N	pepe	f	
9	36	2008-02-10	40000001	500.00	0.00	Vto. Proveedor A de 01.08.2008			\N	pepe	f	
9	37	2008-02-10	57000000	0.00	500.00	Vto. Proveedor A de 01.08.2008			\N	pepe	f	
10	38	2008-03-15	43000002	174.00	0.00	Ventas a cliente B				pepe	f	
10	39	2008-03-15	70000000	0.00	150.00	Ventas a cliente B				pepe	f	
10	40	2008-03-15	47700000	0.00	24.00	Ventas a cliente B				pepe	f	
11	41	2008-03-15	43000002	0.00	174.00	Vto. Cliente B de 15.03.2008			\N	pepe	f	
11	42	2008-03-15	57000000	174.00	0.00	Vto. Cliente B de 15.03.2008			\N	pepe	f	
12	43	2008-03-16	60000000	1000.00	0.00	Compra a proveedor A				pepe	f	
12	44	2008-03-16	47200000	160.00	0.00	Compra a proveedor A				pepe	f	
12	45	2008-03-16	40000001	0.00	1160.00	Compra a proveedor A				pepe	f	
13	46	2008-03-16	40000001	1160.00	0.00	Vto. Proveedor A de 16.03.2008			\N	pepe	f	
13	47	2008-03-16	57000000	0.00	1160.00	Vto. Proveedor A de 16.03.2008			\N	pepe	f	
14	48	2008-03-31	47700000	40.00	0.00	liquidación IVA 1T				pepe	f	
14	49	2008-03-31	47200000	0.00	160.00	liquidación IVA 1T				pepe	f	
14	50	2008-03-31	47000000	120.00	0.00	liquidación IVA 1T				pepe	f	
15	51	2008-04-15	47300001	200.00	0.00	Pago a cuenta 1P IS				pepe	f	
15	52	2008-04-15	57000000	0.00	200.00	Pago a cuenta 1P IS				pepe	f	
16	53	2008-04-20	43000001	568.40	0.00	Ventas a cliente A				pepe	f	
16	54	2008-04-20	70000000	0.00	490.00	Ventas a cliente A				pepe	f	
16	55	2008-04-20	47700000	0.00	78.40	Ventas a cliente A				pepe	f	
17	56	2008-04-20	43000001	0.00	568.40	Vto. Cliente A de 20.04.2008			\N	pepe	f	
17	57	2008-04-20	57000000	568.40	0.00	Vto. Cliente A de 20.04.2008			\N	pepe	f	
18	58	2008-06-10	43000002	580.00	0.00	Ventas cliente B				pepe	f	
18	59	2008-06-10	70000000	0.00	500.00	Ventas cliente B				pepe	f	
18	60	2008-06-10	47700000	0.00	80.00	Ventas cliente B				pepe	f	
19	61	2008-06-10	43000002	0.00	580.00	Vto. Cliente B de 10.06.2008			\N	pepe	f	
19	62	2008-06-10	57000000	580.00	0.00	Vto. Cliente B de 10.06.2008			\N	pepe	f	
20	63	2008-06-30	12900000	5600.00	0.00	Pérdidas y ganancias				pepe	f	
20	64	2008-06-30	11200000	0.00	500.00	Pérdidas y ganancias				pepe	f	
20	65	2008-06-30	11300000	0.00	5100.00	Pérdidas y ganancias				pepe	f	
21	66	2008-06-30	47700000	158.40	0.00	liquidación IVA 2T				pepe	f	
21	67	2008-06-30	47500000	0.00	38.40	liquidación IVA 2T				pepe	f	
21	68	2008-06-30	47000000	0.00	120.00	liquidación IVA 2T				pepe	f	
22	69	2008-07-10	47500000	38.40	0.00	Pago IVA				pepe	f	
22	70	2008-07-10	57000000	0.00	38.40	Pago IVA				pepe	f	
23	71	2008-07-12	21700003	900.00	0.00	Proveedor de inmovilizado a CP				pepe	f	
23	72	2008-07-12	47200000	144.00	0.00	Proveedor de inmovilizado a CP				pepe	f	
23	73	2008-07-12	52300001	0.00	1044.00	Proveedor de inmovilizado a CP				pepe	f	
24	74	2008-07-12	52300001	1044.00	0.00	pago equipo proceso información				pepe	f	
24	75	2008-07-12	57000000	0.00	1044.00	pago equipo proceso información				pepe	f	
25	76	2008-07-20	43000001	5800.00	0.00	Ventas cliente A				pepe	f	
25	77	2008-07-20	70000000	0.00	5000.00	Ventas cliente A				pepe	f	
25	78	2008-07-20	47700000	0.00	800.00	Ventas cliente A				pepe	f	
26	79	2008-07-20	43000001	0.00	5800.00	Vto. Cliente A de 20.07.2008			\N	pepe	f	
26	80	2008-07-20	57000000	5800.00	0.00	Vto. Cliente A de 20.07.2008			\N	pepe	f	
27	81	2008-07-22	47520000	300.00	0.00	Pago IS 2007				pepe	f	
27	82	2008-07-22	57000000	0.00	300.00	Pago IS 2007				pepe	f	
28	83	2008-09-30	47700000	800.00	0.00	liquidación IVA 3t				pepe	f	
28	84	2008-09-30	47200000	0.00	144.00	liquidación IVA 3t				pepe	f	
28	85	2008-09-30	47500000	0.00	656.00	liquidación IVA 3t				pepe	f	
29	86	2008-10-12	47500000	656.00	0.00	ingreso IVA 3T				pepe	f	
29	87	2008-10-12	57000000	0.00	656.00	ingreso IVA 3T				pepe	f	
30	88	2008-10-12	47300001	250.00	0.00	Pago a cuenta 2P				pepe	f	
30	89	2008-10-12	57000000	0.00	250.00	Pago a cuenta 2P				pepe	f	
31	90	2008-11-10	70000000	0.00	2000.00	Cliente B				pepe	f	
31	91	2008-11-10	47700000	0.00	320.00	Cliente B				pepe	f	
31	92	2008-11-10	43000002	2320.00	0.00	Cliente B				pepe	f	
32	93	2008-11-10	43000002	0.00	2320.00	Vto. Cliente B de 10.11.2008			\N	pepe	f	
32	94	2008-11-10	57000000	2320.00	0.00	Vto. Cliente B de 10.11.2008			\N	pepe	f	
33	95	2008-12-14	47300001	250.00	0.00	Pago a cuenta IS 3P				pepe	f	
33	96	2008-12-14	57000000	0.00	250.00	Pago a cuenta IS 3P				pepe	f	
34	97	2008-12-31	47700000	320.00	0.00	liquidación IVA 4T				pepe	f	
34	98	2008-12-31	47500000	0.00	320.00	liquidación IVA 4T				pepe	f	
35	99	2008-12-31	61000001	24000.00	0.00	regularización saldo mercaderías				pepe	f	
35	100	2008-12-31	30000000	0.00	24000.00	regularización saldo mercaderías				pepe	f	
36	101	2008-12-31	30000000	23000.00	0.00	Saldos finales mercaderías				pepe	f	
36	102	2008-12-31	61000001	0.00	23000.00	Saldos finales mercaderías				pepe	f	
37	103	2008-12-31	28110001	0.00	500.00	Amortización del inmovilizado				pepe	f	
37	104	2008-12-31	28160001	0.00	800.00	Amortización del inmovilizado				pepe	f	
37	105	2008-12-31	28170001	0.00	250.00	Amortización del inmovilizado				pepe	f	
37	106	2008-12-31	28170002	0.00	200.00	Amortización del inmovilizado				pepe	f	
37	107	2008-12-31	28170003	0.00	106.64	Amortización del inmovilizado				pepe	f	
37	108	2008-12-31	68100001	1856.64	0.00	Amortización del inmovilizado				pepe	f	
38	109	2008-12-31	63000000	1077.00	0.00	Liquidación impuesto sobre sociedades				pepe	f	
38	110	2008-12-31	47300001	0.00	700.00	Liquidación impuesto sobre sociedades				pepe	f	
38	111	2008-12-31	47520000	0.00	377.00	Liquidación impuesto sobre sociedades				pepe	f	
39	112	2008-12-31	63010001	238.01	0.00	Cálculo del impuesto diferido				pepe	f	
39	113	2008-12-31	47900001	0.00	238.01	Cálculo del impuesto diferido				pepe	f	
40	114	2008-12-31	68100001	0.00	1856.64	REGULARIZACIÓN		REGULARIZACION	\N	pepe	f	
40	115	2008-12-31	70000000	8240.00	0.00	REGULARIZACIÓN		REGULARIZACION	\N	pepe	f	
40	116	2008-12-31	60000000	0.00	1000.00	REGULARIZACIÓN		REGULARIZACION	\N	pepe	f	
40	117	2008-12-31	61000001	0.00	1000.00	REGULARIZACIÓN		REGULARIZACION	\N	pepe	f	
40	118	2008-12-31	63000000	0.00	1077.00	REGULARIZACIÓN		REGULARIZACION	\N	pepe	f	
40	119	2008-12-31	63010001	0.00	238.01	REGULARIZACIÓN		REGULARIZACION	\N	pepe	f	
40	120	2008-12-31	12900000	0.00	3068.35	REGULARIZACIÓN		REGULARIZACION	\N	pepe	f	
41	121	2008-12-31	10000000	60000.00	0.00	CIERRE DE EJERCICIO		CIERRE	\N	pepe	f	
41	122	2008-12-31	11200000	8000.00	0.00	CIERRE DE EJERCICIO		CIERRE	\N	pepe	f	
41	123	2008-12-31	12900000	3068.35	0.00	CIERRE DE EJERCICIO		CIERRE	\N	pepe	f	
41	124	2008-12-31	21000001	0.00	20000.00	CIERRE DE EJERCICIO		CIERRE	\N	pepe	f	
41	125	2008-12-31	21100001	0.00	25000.00	CIERRE DE EJERCICIO		CIERRE	\N	pepe	f	
41	126	2008-12-31	28110001	1750.00	0.00	CIERRE DE EJERCICIO		CIERRE	\N	pepe	f	
41	127	2008-12-31	21600001	0.00	4000.00	CIERRE DE EJERCICIO		CIERRE	\N	pepe	f	
41	128	2008-12-31	21700001	0.00	1000.00	CIERRE DE EJERCICIO		CIERRE	\N	pepe	f	
41	129	2008-12-31	28160001	2800.00	0.00	CIERRE DE EJERCICIO		CIERRE	\N	pepe	f	
41	130	2008-12-31	21700002	0.00	800.00	CIERRE DE EJERCICIO		CIERRE	\N	pepe	f	
41	131	2008-12-31	28170001	750.00	0.00	CIERRE DE EJERCICIO		CIERRE	\N	pepe	f	
41	132	2008-12-31	28170002	400.00	0.00	CIERRE DE EJERCICIO		CIERRE	\N	pepe	f	
41	133	2008-12-31	30000000	0.00	23000.00	CIERRE DE EJERCICIO		CIERRE	\N	pepe	f	
41	134	2008-12-31	47500000	320.00	0.00	CIERRE DE EJERCICIO		CIERRE	\N	pepe	f	
41	135	2008-12-31	47520000	377.00	0.00	CIERRE DE EJERCICIO		CIERRE	\N	pepe	f	
41	136	2008-12-31	57000000	0.00	8210.00	CIERRE DE EJERCICIO		CIERRE	\N	pepe	f	
41	137	2008-12-31	11300000	5100.00	0.00	CIERRE DE EJERCICIO		CIERRE	\N	pepe	f	
41	138	2008-12-31	21700003	0.00	900.00	CIERRE DE EJERCICIO		CIERRE	\N	pepe	f	
41	139	2008-12-31	28170003	106.64	0.00	CIERRE DE EJERCICIO		CIERRE	\N	pepe	f	
41	140	2008-12-31	47900001	238.01	0.00	CIERRE DE EJERCICIO		CIERRE	\N	pepe	f	
\.


--
-- Data for Name: diarios; Type: TABLE DATA; Schema: public; Owner: pepe
--

COPY diarios (codigo, descripcion) FROM stdin;
\.


--
-- Data for Name: dif_conciliacion; Type: TABLE DATA; Schema: public; Owner: pepe
--

COPY dif_conciliacion (codigo, descripcion) FROM stdin;
\.


--
-- Data for Name: ejercicios; Type: TABLE DATA; Schema: public; Owner: pepe
--

COPY ejercicios (codigo, apertura, cierre, cerrado, cerrando, primerasiento, base_ejercicio, base_presupuesto, presupuesto_base_cero, incremento) FROM stdin;
2008	2008-01-01	2008-12-31	t	f	1			t	0.0000
\.


--
-- Data for Name: equivalenciasplan; Type: TABLE DATA; Schema: public; Owner: pepe
--

COPY equivalenciasplan (cod, equiv) FROM stdin;
\.


--
-- Data for Name: estados; Type: TABLE DATA; Schema: public; Owner: pepe
--

COPY estados (titulo, apartado, parte1, clave, nodo, formula, referencia, importe1, importe2, calculado) FROM stdin;
BALANCE PYMES PLAN 2007	A) ACTIVO NO CORRIENTE	t	A	A	{A.1(1)}+{A.2(1)}+{A.3(1)}+{A.4(1)}+{A.5(1)}+{A.6(1)}		0.00	0.00	f
BALANCE PYMES PLAN 2007	I. Inmovilizado intangible	t	1	A.1	[20]+[280]+[290]		0.00	0.00	f
BALANCE PYMES PLAN 2007	II. Inmovilizado material	t	2	A.2	[21]+[281]+[291]+[23]		0.00	0.00	f
BALANCE PYMES PLAN 2007	III. Inversiones inmobiliarias	t	3	A.3	[22]+[282]+[292]		0.00	0.00	f
BALANCE PYMES PLAN 2007	IV. Inversiones en empresas del grupo y asociadas a largo plazo	t	4	A.4	[2403]+[2404]+[2413]+[2414]+[2423]+[2424]+[2493]+[2494]+[2933]+[2934]+[2943]+[2944] + [2953] + [2954]		0.00	0.00	f
BALANCE PYMES PLAN 2007	V. Inversiones financieras a largo plazo	t	5	A.5	[2405]+[2415]+[2425]+ [2495]  +[250]+[251]+[252]+[253]+[254] +[255]+[258]+[259]+[26]+[2935]+[2945]+ [2955]+ [296]+ [297]+ [298]		0.00	0.00	f
BALANCE PYMES PLAN 2007	VI. Activos por impuesto diferido	t	6	A.6	[474]		0.00	0.00	f
BALANCE PYMES PLAN 2007	B) ACTIVO CORRIENTE	t	B	B	{B.1(1)}+{B.2(1)}+{B.3(1)}+{B.4(1)}+{B.5(1)}+{B.6(1)}		0.00	0.00	f
BALANCE PYMES PLAN 2007	I. Existencias	t	1	B.1	[30]+[31]+[32]+[33]+[34]+[35]+[36]+[39]+[407]		0.00	0.00	f
BALANCE PYMES PLAN 2007	II. Deudores comerciales y otras cuentas a cobrar	t	2	B.2	{B.2.1(1)}+{B.2.2(1)}+{B.2.3(1)}		0.00	0.00	f
BALANCE PYMES PLAN 2007	1. Clientes por ventas y Prestaciones de servicios	t	1	B.2.1	[430]+[431]+[432]+[433]+[434]+[435]+[436]+[437]+[490]+[493]		0.00	0.00	f
BALANCE PYMES PLAN 2007	2. Accionistas (socios) por desembolsos exigidos	t	2	B.2.2	[5580]		0.00	0.00	f
BALANCE PYMES PLAN 2007	3. Otros deudores	t	3	B.2.3	[44]+[460]+[470]+[471]+[472]+[544]		0.00	0.00	f
BALANCE PYMES PLAN 2007	III. Inversiones en empresas del grupo y asociadas a corto  plazo	t	3	B.3	[5303]+[5304]+[5313]+[5314]+[5323]+[5324]+[5333]+[5334]+[5343]+[5344]+[5353]+[5354]+[5393]+[5394]+[5523]+ [5524]+ [5933]+[5934]+ [5943]+[5944]+[5953]+[5954]		0.00	0.00	f
BALANCE PYMES PLAN 2007	IV. Inversiones financieras a corto plazo	t	4	B.4	[5305]+[5315]+[5325]+[5335]+[5345]+[5355]+[5395]+[540]+[541]+[542]+[543]+[545]+[546]+[547]+[548]+[549]+[551+] +[5525+] +[5590]+[565]+[566]+[5935]+[5945]+[5955]+[596]+[597]+[598]		0.00	0.00	f
BALANCE PYMES PLAN 2007	V. Periodificaciones a corto plazo	t	5	B.5	[480]+[567]		0.00	0.00	f
BALANCE PYMES PLAN 2007	VI. Efectivo y otros activos líquidos equivalentes	t	6	B.6	[57]		0.00	0.00	f
BALANCE PYMES PLAN 2007	TOTAL ACTIVO (A+B)	t	TOTAL	TOTAL	{A(1)}+{B(1)}		0.00	0.00	f
BALANCE PYMES PLAN 2007	A) PATRIMONIO NETO	f	A	A	{A.1(2)}+{A.2(2)}		0.00	0.00	f
BALANCE PYMES PLAN 2007	A-1) Fondos propios	f	1	A.1	{A.1.1(2)}+{A.1.2(2)}+{A.1.3(2)}+{A.1.4(2)}+{A.1.5(2)}+{A.1.6(2)}+{A.1.7(2)}+{A.1.8(2)}		0.00	0.00	f
BALANCE PYMES PLAN 2007	I. Capital	f	1	A.1.1	{A.1.1.1(2)}+{A.1.1.2(2)}		0.00	0.00	f
BALANCE PYMES PLAN 2007	1. Capital escriturado	f	1	A.1.1.1	-[100]-[101]-[102]		0.00	0.00	f
BALANCE PYMES PLAN 2007	2. Capital no exigido	f	2	A.1.1.2	-[1030]-[1040]		0.00	0.00	f
BALANCE PYMES PLAN 2007	II. Prima de emisión	f	2	A.1.2	-[110]		0.00	0.00	f
BALANCE PYMES PLAN 2007	III. Reservas	f	3	A.1.3	-[112]-[113]-[114]-[119]		0.00	0.00	f
BALANCE PYMES PLAN 2007	IV. Acciones y participaciones en patrimonio propias	f	4	A.1.4	-[108]-[109]		0.00	0.00	f
BALANCE PYMES PLAN 2007	V. Resultados de ejercicios anteriores	f	5	A.1.5	-[120]-[121]		0.00	0.00	f
BALANCE PYMES PLAN 2007	VI. Otras aportaciones de socios	f	6	A.1.6	-[118]		0.00	0.00	f
BALANCE PYMES PLAN 2007	VII. Resultado del ejercicio	f	7	A.1.7	-[129]		0.00	0.00	f
BALANCE PYMES PLAN 2007	VIII. Dividendo a cuenta	f	8	A.1.8	-[557]		0.00	0.00	f
BALANCE PYMES PLAN 2007	A-2) Subvenciones, donaciones y legados recibidos	f	2	A.2	-[130]-[131]-[132]		0.00	0.00	f
BALANCE PYMES PLAN 2007	B) PASIVO NO CORRIENTE	f	B	B	{B.1(2)}+{B.2(2)}+{B.3(2)}+{B.4(2)}+{B.5(2)}		0.00	0.00	f
BALANCE PYMES PLAN 2007	I. Provisiones a largo plazo	f	1	B.1	-[14]		0.00	0.00	f
BALANCE PYMES PLAN 2007	II. Deudas a largo plazo	f	2	B.2	{B.2.1(2)}+{B.2.2(2)}+{B.2.3(2)}		0.00	0.00	f
BALANCE PYMES PLAN 2007	1. Deudas con entidades de crédito	f	1	B.2.1	-[1605]-[170]		0.00	0.00	f
BALANCE PYMES PLAN 2007	2. Acreedores por arrendamiento financiero	f	2	B.2.2	-[1625]-[174]		0.00	0.00	f
BALANCE PYMES PLAN 2007	3. Otras deudas a largo plazo	f	3	B.2.3	-[1615]-[1635]-[171]-[172]-[173]-[175]-[176]-[177]-[179]-[180]-[185]		0.00	0.00	f
BALANCE PYMES PLAN 2007	III. Deudas con empresas del grupo y asociadas a largo plazo	f	3	B.3	-[1603]-[1604]-[1613]-[1614]-[1623]-[1624]-[1633]-[1634]		0.00	0.00	f
BALANCE PYMES PLAN 2007	IV. Pasivos por impuesto diferido	f	4	B.4	-[479]		0.00	0.00	f
BALANCE PYMES PLAN 2007	V. Periodificaciones a largo plazo	f	5	B.5	-[181]		0.00	0.00	f
BALANCE PYMES PLAN 2007	C) PASIVO CORRIENTE	f	C	C	{C.1(2)}+{C.2(2)}+{C.3(2)}+{C.4(2)}+{C.5(2)}		0.00	0.00	f
BALANCE PYMES PLAN 2007	I. Provisiones a corto plazo	f	1	C.1	-[499]-[529]		0.00	0.00	f
BALANCE PYMES PLAN 2007	II. Deudas a corto plazo	f	2	C.2	{C.2.1(2)}+{C.2.2(2)}+{C.2.3(2)}		0.00	0.00	f
BALANCE PYMES PLAN 2007	1. Deudas con entidades de crédito	f	1	C.2.1	-[5105]-[520]-[527]		0.00	0.00	f
BALANCE PYMES PLAN 2007	2. Acreedores por arrendamiento financiero	f	2	C.2.2	-[5125]-[524]		0.00	0.00	f
BALANCE PYMES PLAN 2007	3. Otras deudas a corto plazo	f	3	C.2.3	-[1034]-[1044]-[190]-[192]-[194]-[500]-[505]-[506]-[509]-[5115]-[5135]-[5145]-[521]-[522]-[523]-[525]-[526]-[528]-[551-]-[5525-]- [555]- [5565] -[5566]-[5595]-[560]-[561]		0.00	0.00	f
BALANCE PYMES PLAN 2007	III. Deudas con empresas del grupo y asociadas a corto plazo	f	3	C.3	-[5103]-[5104]-[5113]-[5114]-[5123]-[5124]-[5133]-[5134]-[5143]-[5144]-[5523]-[5524]-[5563]-[5564]		0.00	0.00	f
BALANCE PYMES PLAN 2007	IV. Acreedores comerciales y otras cuentas a pagar	f	4	C.4	{C.4.1(2)}+{C.4.2(2)}		0.00	0.00	f
BALANCE PYMES PLAN 2007	1. Proveedores	f	1	C.4.1	-[400]-[401]-[403]-[404]-[405]-[406]		0.00	0.00	f
BALANCE PYMES PLAN 2007	2. Otros acreedores	f	2	C.4.2	-[41]-[438]-[465]-[475]-[476]-[477]		0.00	0.00	f
BALANCE PYMES PLAN 2007	V. Periodificaciones	f	5	C.5	-[485]-[568]		0.00	0.00	f
BALANCE PYMES PLAN 2007	TOTAL PATRIMONIO NETO Y PASIVO (A + B + C)	f	TOTAL	TOTAL	{A(2)}+{B(2)}+{C(2)}		0.00	0.00	f
CUENTA PÉRDIDAS Y GANANCIAS PYMES PLAN 2007	1. Importe neto de la cifra de negocios	t	01	01	-[700]-[701]-[702]-[703]-[704]-[705]-[706]-[708]-[709]		0.00	0.00	f
CUENTA PÉRDIDAS Y GANANCIAS PYMES PLAN 2007	2. Variación de existencias de productos terminados y en curso de fabricación	t	02	02	-[71]-[6930]-[7930]		0.00	0.00	f
CUENTA PÉRDIDAS Y GANANCIAS PYMES PLAN 2007	3. Trabajos realizados por la empresa para su activo	t	03	03	-[73]		0.00	0.00	f
CUENTA PÉRDIDAS Y GANANCIAS PYMES PLAN 2007	4. Aprovisionamientos	t	04	04	-[600]-[601]-[602]-[606]-[607]-[608]-[609]-[61]-[6931]-[6932]-[6933]-[7931]-[7932]-[7933]		0.00	0.00	f
CUENTA PÉRDIDAS Y GANANCIAS PYMES PLAN 2007	5. Otros ingresos de explotación	t	05	05	-[740]-[747]-[75]		0.00	0.00	f
CUENTA PÉRDIDAS Y GANANCIAS PYMES PLAN 2007	6. Gastos de personal	t	06	06	-[64]		0.00	0.00	f
CUENTA PÉRDIDAS Y GANANCIAS PYMES PLAN 2007	7. Otros gastos de explotación	t	07	07	-[62]-[631]-[634]-[636]-[639]-[65]-[694]-[695]-[794]-[7954]		0.00	0.00	f
CUENTA PÉRDIDAS Y GANANCIAS PYMES PLAN 2007	8. Amortización del inmovilizado	t	08	08	-[68]		0.00	0.00	f
CUENTA PÉRDIDAS Y GANANCIAS PYMES PLAN 2007	9. Imputación de subvenciones de inmovilizado no financiero y otras	t	09	09	-[746]		0.00	0.00	f
CUENTA PÉRDIDAS Y GANANCIAS PYMES PLAN 2007	10. Excesos de provisiones	t	10	10	-[7951]-[7952]-[7955]		0.00	0.00	f
CUENTA PÉRDIDAS Y GANANCIAS PYMES PLAN 2007	11. Deterioro y resultado por enajenaciones del inmovilizado	t	11	11	-[670]-[671]-[672]-[690]-[691]-[692]-[770]-[771]-[772]-[790]-[791]-[792]		0.00	0.00	f
CUENTA PÉRDIDAS Y GANANCIAS PYMES PLAN 2007	12. Ingresos financieros	t	12	12	-[760]-[761]-[762]-[769]		0.00	0.00	f
CUENTA PÉRDIDAS Y GANANCIAS PYMES PLAN 2007	13. Gastos financieros	t	13	13	-[660]-[661]-[662]-[664]-[665]-[669]		0.00	0.00	f
CUENTA PÉRDIDAS Y GANANCIAS PYMES PLAN 2007	14. Variación del valor razonable en instrumentos financieros	t	14	14	-[663]-[763]		0.00	0.00	f
CUENTA PÉRDIDAS Y GANANCIAS PYMES PLAN 2007	15. Diferencias de cambio	t	15	15	-[668]-[768]		0.00	0.00	f
CUENTA PÉRDIDAS Y GANANCIAS PYMES PLAN 2007	16. Deterioro y resultado por enajenaciones de instrumentos financieros	t	16	16	-[666]-[667]-[673]-[675]-[696]-[697]-[698]-[699]-[766]-[773]-[775]-[796]-[797]-[798]-[799]		0.00	0.00	f
CUENTA PÉRDIDAS Y GANANCIAS PYMES PLAN 2007	17. Impuesto sobre beneficios	t	17	17	-[6300]-[6301]-[633]-[638]		0.00	0.00	f
CUENTA PÉRDIDAS Y GANANCIAS PYMES PLAN 2007	A) RESULTADO DE EXPLOTACIÓN (1 + 2 + 3 + 4 + 5 + 6 + 7 + 8 + 9 + 10 + 11 )	t	11A	11A	{01(1)}+{02(1)}+{03(1)}+{04(1)}+{05(1)}+{06(1)}+{07(1)}+{08(1)}+{09(1)}+{10(1)}+{11(1)}		0.00	0.00	f
CUENTA PÉRDIDAS Y GANANCIAS PYMES PLAN 2007	B) RESULTADO FINANCIERO (12+13+14+15+16)	t	16B	16B	{12(1)}+{13(1)}+{14(1)}+{15(1)}+{16(1)}		0.00	0.00	f
CUENTA PÉRDIDAS Y GANANCIAS PYMES PLAN 2007	C) RESULTADO ANTES DE IMPUESTOS (A+B)	t	16C	16C	{11A(1)}+{16B(1)}		0.00	0.00	f
CUENTA PÉRDIDAS Y GANANCIAS PYMES PLAN 2007	D) RESULTADO DEL EJERCICIO (C+17)	t	18D	18D	{16C(1)}+{17(1)}		0.00	0.00	f
\.


--
-- Data for Name: libroiva; Type: TABLE DATA; Schema: public; Owner: pepe
--

COPY libroiva (pase, cta_base_iva, base_iva, clave_iva, tipo_iva, tipo_re, cuota_iva, cuenta_fra, fecha_fra, soportado, aib, eib, prorrata, rectificativa, autofactura) FROM stdin;
27	70000000	100.00	GN	16.00	0.00	16.00	43000001	2008-01-10	f	f	f	1.00	f	f
40	70000000	150.00	GN	16.00	0.00	24.00	43000002	2008-03-15	f	f	f	1.00	f	f
44	60000000	1000.00	GN	16.00	0.00	160.00	40000001	2008-03-16	t	f	f	1.00	f	f
55	70000000	490.00	GN	16.00	0.00	78.40	43000001	2008-04-20	f	f	f	1.00	f	f
60	70000000	500.00	GN	16.00	0.00	80.00	43000002	2008-06-10	f	f	f	1.00	f	f
72	21700003	900.00	GN	16.00	0.00	144.00	52300001	2008-07-12	t	f	f	1.00	f	f
78	70000000	5000.00	GN	16.00	0.00	800.00	43000001	2008-07-20	f	f	f	1.00	f	f
91	70000000	2000.00	GN	16.00	0.00	320.00	43000002	2008-11-10	f	f	f	1.00	f	f
\.


--
-- Data for Name: nuevoplan; Type: TABLE DATA; Schema: public; Owner: pepe
--

COPY nuevoplan (codigo, descripcion) FROM stdin;
\.


--
-- Data for Name: periodos; Type: TABLE DATA; Schema: public; Owner: pepe
--

COPY periodos (ejercicio, codigo, inicio, fin) FROM stdin;
\.


--
-- Data for Name: planamortizaciones; Type: TABLE DATA; Schema: public; Owner: pepe
--

COPY planamortizaciones (cuenta_activo, fecha_func, codigo_activo, cuenta_am_acum, cuenta_gasto, valor_residual, amort_personalizada, coef_amort_contable, coef_amort_fiscal, amort_fiscal_1ejer) FROM stdin;
21100001	2002-07-01		28110001	68100001	0.00	f	0.02	0	f
21600001	2005-07-01		28160001	68100001	0.00	f	0.20000000000000001	0	f
21700001	2006-01-01		28170001	68100001	0.00	f	0.25	0	f
21700002	2007-01-01		28170002	68100001	0.00	f	0.25	0	f
21700003	2008-07-12	PC3	28170003	68100001	0.00	f	0.25	0	t
\.


--
-- Data for Name: plancontable; Type: TABLE DATA; Schema: public; Owner: pepe
--

COPY plancontable (codigo, descripcion, auxiliar) FROM stdin;
1	FINANCIACIÓN BÁSICA	f
10	CAPITAL	f
100	Capital social	f
101	Fondo social	f
102	Capital	f
103	Socios por desembolsos no exigidos	f
104	Socios por aportaciones no dinerarias pendientes	f
108	Acciones o participaciones propias en situaciones especiales	f
109	Acciones o participaciones propias para reducción de capital	f
11	RESERVAS	f
110	Prima de emisión o asunción	f
112	Reservas legal	f
113	Reserva voluntaria	f
114	Reservas especiales	f
1140	Reservas para acciones o participaciones de la sociedad dominante	f
1141	Reservas estatutarias	f
1142	Reservas por capital amortizado	f
118	Aportaciones de socios o propietarios	f
119	Diferencias por ajuste del capital a euros	f
12	RESULTADOS PENDIENTES DE APLICACIÓN	f
120	Remanente	f
121	Resultados negativos de ejercicios anteriores	f
13	SUBVENCIONES, DONACIONES Y AJUSTES POR CAMBIOS DE VALOR	f
130	Subvenciones oficiales de capital	f
131	Donaciones y legados de capital	f
132	Otras subvenciones, donaciones y legados	f
137	Ingresos fiscales a distribuir en varios ejercicios	f
1370	Ingresos fiscales por diferencias permanentes a distribuir en varios ejercicios	f
1371	Ingresos fiscales por deducciones y bonificaciones a distribuir en varios ejercicios	f
14	PROVISIONES	f
141	Provisión para impuestos	f
142	Provisión para otras responsabilidades	f
143	Provisión por desmantelamiento, retiro o rehabilitación del inmovilizado.	f
145	Provisión para actuaciones medioambientales	f
15	DEUDAS A LARGO PLAZO CON CARACTERÍSTICAS ESPECIALES	f
150	Acciones o participaciones a largo plazo contabilizadas como pasivo	f
153	Desembolsos no exigidos por acciones o participaciones contabilizadas como pasivo	f
1533	Desembolsos no exigidos, empresas del grupo	f
1534	Desembolsos no exigidos, empresas asociadas	f
1535	Desembolsos no exigidos, otras partes vinculadas	f
1536	Otros desembolsos no exigidos	f
1543	Aportaciones no dinerarias pendientes, empresas del grupo	f
1544	Aportaciones no dinerarias pendientes, empresas asociadas	f
1545	Aportaciones no dinerarias pendientes, otras partes vinculadas	f
1546	Otras aportaciones no dinerarias pendientes	f
16	DEUDAS A LARGO PLAZO CON PARTES VINCULADAS	f
160	Deudas a largo plazo con entidades de crédito vinculadas	f
1603	Deudas a largo plazo con entidades de crédito, empresas del grupo	f
1604	Deudas a largo plazo con entidades de crédito, empresas asociadas	f
1605	Deudas a largo plazo con otras entidades de crédito vinculadas	f
161	Proveedores de inmovilizado a largo plazo, partes vinculadas	f
1613	Proveedores de inmovilizado a largo plazo, empresas del grupo	f
1614	Proveedores de inmovilizado a largo plazo, empresas asociadas	f
1615	Proveedores de inmovilizado a largo plazo, otras partes vinculadas	f
17	DEUDAS A LARGO PLAZO POR PRÉSTAMOS RECIBIDOS Y OTROS CONCEPTOS	f
170	Deudas a largo plazo con entidades de crédito	f
171	Deudas a largo plazo	f
172	Deudas a largo plazo transformables en subvenciones	f
173	Proveedores de inmovilizado a largo plazo	f
18	PASIVOS POR FIANZAS Y GARANTÍAS A LARGO PLAZO	f
180	Fianzas recibidas a largo plazo	f
185	Depósitos recibidos a largo plazo	f
19	SITUACIONES TRANSITORIAS DE FINANCIACIÓN	f
190	Acciones o participaciones emitidas	f
192	Suscriptores de acciones	f
2	INMOVILIZADO	f
20	INMOVILIZACIONES INTANGIBLES	f
209	Anticipos para inmovilizaciones intangibles	f
21	INMOVILIZACIONES MATERIALES	f
210	Terrenos y bienes naturales	f
211	Construcciones	f
212	Instalaciones técnicas	f
213	Maquinaria	f
214	Utillaje	f
215	Otras instalaciones	f
216	Mobiliario	f
217	Equipos para procesos de información	f
218	Elementos de transporte	f
219	Otro inmovilizado material	f
22	INVERSIONES INMOBILIARIAS	f
220	Terrenos y bienes naturales	f
221	Construcciones	f
23	INMOVILIZACIONES MATERIALES EN CURSO	f
230	Adaptación de terrenos y bienes naturales	f
231	Construcciones en curso	f
232	Instalaciones técnicas en montaje	f
233	Maquinaria en montaje	f
237	Equipos para procesos de información en montaje	f
239	Anticipos para inmovilizaciones materiales	f
240	Participaciones a largo plazo en partes vinculadas	f
2403	Participaciones a largo plazo en empresas del grupo	f
2404	Participaciones a largo plazo en empresas asociadas	f
2405	Participaciones a largo plazo en otras partes vinculadas	f
241	Valores representativos de deuda a largo plazo de partes vinculadas	f
2413	Valores representativos de deuda a largo plazo de empresas del grupo	f
2414	Valores representativos de deuda a largo plazo de empresas asociadas	f
2415	Valores representativos de deuda a largo plazo de otras partes vinculadas	f
242	Créditos a largo plazo a partes vinculadas	f
2423	Créditos a largo plazo a empresas del grupo	f
2424	Créditos a largo plazo a empresas asociadas	f
2425	Créditos a largo plazo a otras partes vinculadas	f
25	OTRAS INVERSIONES FINANCIERAS A LARGO PLAZO	f
250	Inversiones financieras a largo plazo en instrumentos de patrimonio	f
251	Valores representativos de deuda a largo plazo	f
252	Créditos a largo plazo	f
253	Créditos a largo plazo por enajenación de inmovilizado	f
254	Créditos a largo plazo al personal	f
255	Activos por derivados financieros a largo plazo	f
258	Imposiciones a largo plazo	f
26	FIANZAS Y DEPÓSITOS CONSTITUIDOS A LARGO PLAZO	f
260	Fianzas constituidas a largo plazo	f
265	Depósitos constituidos a largo plazo	f
28	AMORTIZACIÓN ACUMULADA DEL INMOVILIZADO	f
280	Amortización acumulada del inmovilizado intangible	f
281	Amortización acumulada del inmovilizado material	f
2811	Amortización acumulada de construcciones	f
2812	Amortización acumulada de instalaciones técnicas	f
2813	Amortización acumulada de maquinaria	f
2814	Amortización acumulada de utillaje	f
2815	Amortización acumulada de otras instalaciones	f
2816	Amortización acumulada de mobiliario	f
2817	Amortización acumulada de equipos para procesos de información	f
2818	Amortización acumulada de elementos de transporte	f
2819	Amortización acumulada de otro inmovilizado material	f
282	Amortización acumulada de las inversiones inmobiliarias	f
290	Deterioro de valor del inmovilizado intangible	f
291	Deterioro de valor del inmovilizado material	f
2911	Deterioro de valor de construcciones	f
2912	Deterioro de valor de instalaciones técnicas	f
2913	Deterioro de valor de maquinaria	f
2914	Deterioro de valor de utillaje	f
2915	Deterioro de valor de otras instalaciones	f
2916	Deterioro de valor de mobiliario	f
2917	Deterioro de valor de equipos para procesos de información	f
2918	Deterioro de valor de elementos de transporte	f
2919	Deterioro de valor de otro inmovilizado material	f
292	Deterioro de valor de las inversiones inmobiliarias	f
2920	Deterioro de valor de los terrenos y bienes naturales	f
2921	Deterioro de valor de construcciones	f
293	Deterioro de valor de participaciones a largo plazo en partes vinculadas	f
2933	Deterioro de valor de participaciones a largo plazo en empresas del grupo	f
2934	Deterioro de valor de participaciones a largo plazo en empresas asociadas	f
2935	Deterioro de valor de participaciones a largo plazo en otras partes vinculadas	f
294	Deterioro de valores representativos de deuda a largo plazo de partes vinculadas	f
295	Deterioro de valor de créditos a largo plazo a partes vinculadas	f
2953	Deterioro de valor de créditos a largo plazo a empresas del grupo	f
2954	Deterioro de valor de créditos a largo plazo a empresas asociadas	f
2955	Deterioro de valor de créditos a largo plazo a otras partes vinculadas	f
296	Deterioro de valor de participaciones en el patrimonio neto a largo plazo	f
297	Deterioro de valor de valores representativos de deuda a largo plazo	f
298	Deterioro de valor de créditos a largo plazo	f
3	EXISTENCIAS	f
30	COMERCIALES	f
300	Mercaderías A	f
301	Mercaderías B	f
31	MATERIAS PRIMAS	f
310	Materias primas A	f
311	Materias primas B	f
32	OTROS APROVISIONAMIENTOS	f
320	Elementos y conjuntos incorporables	f
321	Combustibles	f
322	Repuestos	f
325	Materiales diversos	f
326	Embalajes	f
327	Envases	f
328	Material de oficina	f
33	PRODUCTOS EN CURSO	f
330	Productos en curso A	f
331	Productos en curso B	f
34	PRODUCTOS SEMITERMINADOS	f
340	Productos semiterminados A	f
341	Productos semiterminados B	f
35	PRODUCTOS TERMINADOS	f
350	Productos terminados A	f
351	Productos terminados B	f
36	SUBPRODUCTOS, RESIDUOS Y MATERIALES RECUPERADOS	f
360	Subproductos A	f
361	Subproductos B	f
365	Residuos A	f
366	Residuos B	f
368	Materiales recuperados A	f
369	Materiales recuperados B	f
39	DETERIORO DE VALOR DE LAS EXISTENCIAS	f
390	Deterioro de valor de las mercaderías	f
391	Deterioro de valor de las materias primas	f
392	Deterioro de valor de otros aprovisionamientos	f
393	Deterioro de valor de los productos en curso	f
394	Deterioro de valor de los productos semiterminados	f
395	Deterioro de valor de los productos terminados	f
396	Deterioro de valor de los subproductos, residuos y materiales recuperados	f
4	ACREEDORES Y DEUDORES POR OPERACIONES COMERCIALES	f
40	PROVEEDORES	f
400	Proveedores	f
4000	Proveedores (euros)	f
4004	Proveedores (moneda extranjera)	f
4009	Proveedores, facturas pendientes de recibir o de formalizar	f
401	Proveedores, efectos comerciales a pagar	f
403	Proveedores, empresas del grupo	f
4030	Proveedores, empresas del grupo (euros)	f
4031	Efectos comerciales a pagar, empresas del grupo	f
4034	Proveedores, empresas del grupo (moneda extranjera)	f
4036	Envases y embalajes a devolver a proveedores, empresas del grupo	f
4039	Proveedores, empresas del grupo, facturas pendientes de recibir o de formalizar	f
404	Proveedores, empresas asociadas	f
405	Proveedores, otras partes vinculadas	f
406	Envases y embalajes a devolver a proveedores	f
407	Anticipos a proveedores	f
41	ACREEDORES VARIOS	f
410	Acreedores por prestaciones de servicios	f
4100	Acreedores por prestaciones de servicios (euros)	f
4104	Acreedores por prestaciones de servicios, (moneda extranjera)	f
4109	Acreedores por prestaciones de servicios, facturas pendientes de recibir o de formalizar	f
411	Acreedores, efectos comerciales a pagar	f
419	Acreedores por operaciones en común	f
43	CLIENTES	f
430	Clientes	f
4300	Clientes (euros)	f
4304	Clientes, (moneda extranjera)	f
4309	Clientes, facturas pendientes de formalizar	f
431	Clientes, efectos comerciales a cobrar	f
4310	Efectos comerciales en cartera	f
4311	Efectos comerciales descontados	f
4312	Efectos comerciales en gestión de cobro	f
4315	Efectos comerciales impagados	f
433	Clientes, empresas del grupo	f
4330	Clientes empresas del grupo (euros)	f
4331	Efectos comerciales a cobrar, empresas del grupo	f
4334	Clientes empresas del grupo, (moneda extranjera)	f
4336	Clientes empresas del grupo de dudoso cobro	f
4337	Envases y embalajes a devolver a clientes, empresas del grupo	f
4339	Clientes empresas del grupo, facturas pendientes de formalizar	f
434	Clientes, empresas asociadas	f
435	Clientes, otras partes vinculadas	f
436	Clientes de dudoso cobro	f
437	Envases y embalajes a devolver por clientes	f
438	Anticipos de clientes	f
44	DEUDORES VARIOS	f
440	Deudores	f
4400	Deudores (euros)	f
4404	Deudores (moneda extranjera)	f
4409	Deudores, facturas pendientes de formalizar	f
441	Deudores, efectos comerciales a cobrar	f
4410	Deudores, efectos comerciales en cartera	f
4411	Deudores, efectos comerciales descontados	f
4412	Deudores, efectos comerciales en gestión de cobro	f
4415	Deudores, efectos comerciales impagados	f
449	Deudores por operaciones en común	f
46	PERSONAL	f
460	Anticipos de remuneraciones	f
465	Remuneraciones pendientes de pago	f
47	ADMINISTRACIONES PÚBLICAS	f
470	Hacienda Pública, deudora por diversos conceptos	f
4700	Hacienda Pública, deudora por IVA	f
4708	Hacienda Pública, deudora por subvenciones concedidas	f
4709	Hacienda Pública, deudora por devolución de impuestos	f
471	Organismos de la Seguridad Social, deudores	f
472	Hacienda Pública, IVA soportado	f
473	Hacienda Pública, retenciones y pagos a cuenta	f
474	Activos por impuesto diferido	f
4740	Diferencias temporarias deducibles	f
4742	Derechos por deducciones y bonificaciones pendientes de aplicar	f
4745	Crédito por pérdidas a compensar del ejercicio	f
475	Hacienda Pública, acreedora por conceptos fiscales	f
4750	Hacienda Pública, acreedora por IVA	f
4751	Hacienda Pública, acreedora por retenciones practicadas	f
4752	Hacienda Pública, acreedora por impuesto sobre sociedades	f
4758	Hacienda Pública, acreedora por subvenciones a reintegrar	f
476	Organismos de la Seguridad Social, acreedores	f
477	Hacienda Pública, IVA repercutido	f
48	AJUSTES POR PERIODIFICACIÓN	f
480	Gastos anticipados	f
485	Ingresos anticipados	f
49	DETERIORO DE VALOR DE CRÉDITOS COMERCIALES Y PROVISIONES A CORTO PLAZO	f
490	Deterioro de valor de créditos por operaciones comerciales	f
493	Deterioro de valor de créditos por operaciones comerciales con partes vinculadas	f
4933	Deterioro de valor de créditos por operaciones comerciales con empresas del grupo	f
4934	Deterioro de valor de créditos por operaciones comerciales con empresas asociadas	f
4935	Deterioro de valor de créditos por operaciones comerciales con otras partes vinculadas	f
4994	Provisión por contratos onerosos	f
4999	Provisión para otras operaciones comerciales	f
5	CUENTAS FINANCIERAS	f
50	EMPRÉSTITOS, DEUDAS CON CARÁCTERÍSTICAS ESPECIALES Y OTRAS EMISIONES ANÁLOGAS A CORTO PLAZO	f
500	Obligaciones y bonos a corto plazo	f
505	Deudas representadas en otros valores negociables a corto plazo	f
506	Intereses de empréstitos y otras emisiones análogas	f
509	Valores negociables amortizados	f
5090	Obligaciones y bonos amortizados	f
5095	Otros valores negociables amortizados	f
51	DEUDAS A CORTO PLAZO CON PARTES VINCULADAS	f
510	Deudas a corto plazo con entidades de crédito vinculadas	f
5103	Deudas a corto plazo con entidades de crédito, empresas del grupo	f
5104	Deudas a corto plazo con entidades de crédito, empresas asociadas	f
5105	Deudas a corto plazo con otras entidades de crédito vinculadas	f
511	Proveedores de inmovilizado a corto plazo, partes vinculadas	f
5113	Proveedores de inmovilizado a corto plazo, empresas del grupo	f
5114	Proveedores de inmovilizado a corto plazo, empresas asociadas	f
5115	Proveedores de inmovilizado a corto plazo, otras partes vinculadas	f
52	DEUDAS A CORTO PLAZO POR PRÉSTAMOS RECIBIDOS Y OTROS CONCEPTOS	f
520	Deudas a corto plazo con entidades de crédito	f
5200	Préstamos a corto plazo de entidades de crédito	f
5201	Deudas a corto plazo por crédito dispuesto	f
5208	Deudas por efectos descontados	f
521	Deudas a corto plazo	f
522	Deudas a corto plazo transformables en subvenciones, donaciones y legados	f
523	Proveedores de inmovilizado a corto plazo	f
529	Provisiones a corto plazo	f
53	INVERSIONES FINANCIERAS A CORTO PLAZO EN PARTES VINCULADAS	f
530	Participaciones a corto plazo en partes vinculadas	f
5303	Participaciones a corto plazo, en empresas del grupo	f
5304	Participaciones a corto plazo, en empresas asociadas	f
5305	Participaciones a corto plazo, en otras partes vinculadas	f
531	Valores representativos de deuda a corto plazo de partes vinculadas	f
5313	Valores representativos de deuda a corto plazo de empresas del grupo	f
5314	Valores representativos de deuda a corto plazo de empresas asociadas	f
5315	Valores representativos de deuda a corto plazo de otras partes vinculadas	f
532	Créditos a corto plazo a partes vinculadas	f
5323	Créditos a corto plazo a empresas del grupo	f
5324	Créditos a corto plazo a empresas asociadas	f
5325	Créditos a corto plazo a otras partes vinculadas	f
54	OTRAS INVERSIONES FINANCIERAS TEMPORALES	f
540	Inversiones financieras temporales en instrumentos de patrimonio	f
541	Valores representativos de deuda a corto plazo	f
542	Créditos a corto plazo	f
543	Créditos a corto plazo por enajenación de inmovilizado	f
544	Créditos a corto plazo al personal	f
545	Dividendo a cobrar	f
548	Imposiciones a corto plazo	f
549	Desembolsos pendientes sobre participaciones en el patrimonio neto a corto plazo	f
55	OTRAS CUENTAS NO BANCARIAS	f
550	Titular de la explotación	f
551	Cuenta corriente con socios y administradores	f
552	Cuenta corriente con otras personas y entidades vinculadas	f
5523	Cuenta corriente con empresas del grupo	f
5524	Cuenta corriente con empresas asociadas	f
5525	Cuenta corriente con otras partes vinculadas	f
554	Cuenta corriente con uniones temporales de empresas y comunidades de bienes	f
555	Partidas pendientes de aplicación	f
556	Desembolsos exigidos sobre participaciones en el patrimonio neto	f
5563	Desembolsos exigidos sobre participaciones, empresas del grupo	f
5564	Desembolsos exigidos sobre participaciones, empresas asociadas	f
5565	Desembolsos exigidos sobre participaciones, otras partes vinculadas	f
5566	Desembolsos exigidos sobre participaciones de otras empresas	f
557	Dividendo activo a cuenta	f
558	Socios por desembolsos exigidos	f
559	Derivados financieros a corto plazo	f
5590	Activos por derivados financieros a corto plazo	f
5591	Pasivos por derivados financieros a corto plazo	f
56	FIANZAS Y DEPÓSITOS RECIBIDOS Y CONSTITUIDOS A CORTO PLAZO, Y AJUSTES POR PERIODIFICACIÓN	f
560	Fianzas recibidas a corto plazo	f
561	Depósitos recibidos a corto plazo	f
565	Fianzas constituidas a corto plazo	f
566	Depósitos constituidos a corto plazo	f
567	Intereses pagados por anticipado	f
568	Intereses cobrados por anticipado	f
57	TESORERÍA	f
570	Caja, euros	f
571	Caja, moneda extranjera	f
572	Bancos e instituciones de crédito c/c vista, euros	f
573	Bancos e instituciones de crédito c/c vista, moneda extranjera	f
574	Bancos e instituciones de crédito, cuentas de ahorro, euros	f
575	Bancos e instituciones de crédito, cuentas de ahorro, moneda extranjera	f
593	Deterioro de valor de participaciones a corto plazo en partes vinculadas	f
5933	Deterioro de valor de participaciones a corto plazo en empresas del grupo	f
5934	Deterioro de valor de participaciones a corto plazo en empresas asociadas	f
5935	Deterioro de valor de participaciones a corto en otras partes vinculadas	f
594	Deterioro de valores representativos de deuda a corto de partes vinculadas	f
5943	Deterioro de valores representativos de deuda a corto plazo de empresas del grupo	f
5944	Deterioro de valores representativos de deuda a corto plazo de empresas asociadas	f
5945	Deterioro de valores representativos de deuda a corto plazo de otras partes vinculadas	f
595	Deterioro de valor de créditos a corto plazo a partes vinculadas	f
5953	Deterioro de valor de créditos a corto plazo a empresas del grupo	f
5954	Deterioro de valor de créditos a corto plazo a empresas asociadas	f
5955	Deterioro de valor de créditos a corto plazo a otras partes vinculadas	f
596	Deterioro de valor de participaciones a corto plazo	f
597	Deterioro de valor de valores representativos de deuda a corto plazo	f
598	Deterioro de valor de créditos a corto plazo	f
6	COMPRAS Y GASTOS	f
60	COMPRAS	f
600	Compras de mercaderías	f
601	Compras de materias primas	f
602	Compras de otros aprovisionamientos	f
606	Descuentos sobre ventas por pronto pago	f
6060	Descuentos sobre compras por pronto pago de mercaderías	f
6061	Descuentos sobre compras por pronto pago de materias primas	f
6062	Descuentos sobre compras por pronto pago de otros aprovisionamientos	f
607	Trabajos realizados por otras empresas	f
608	Devoluciones de compras y operaciones similares	f
6080	Devoluciones de compras de mercaderias	f
6081	Devoluciones de compras de materias primas	f
6082	Devoluciones de compras de otros aprovisionamientos	f
609	"Rappels" por compras	f
6090	"Rappels" por compras de mercaderias	f
6091	"Rappels" por compras de materias primas	f
6092	"Rappels" por compras de otros aprovisionamientos	f
61	VARIACIÓN DE EXISTENCIAS	f
610	Variación de existencias de mercaderías	f
611	Variación de existencias de materias primas	f
612	Variación de existencias de otros aprovisionamientos	f
62	SERVICIOS EXTERIORES	f
620	Gastos en investigación y desarrollo del ejercicio	f
621	Arrendamientos y cánones	f
622	Reparaciones y conservación	f
623	Servicios de profesionales independientes	f
624	Transportes	f
625	Primas de seguros	f
626	Servicios bancarios y similares	f
627	Publicidad, propaganda y relaciones públicas	f
628	Suministros	f
629	Otros servicios	f
63	TRIBUTOS	f
630	Impuesto sobre beneficios	f
6300	Impuesto corriente	f
6301	Impuesto diferido	f
631	Otros tributos	f
633	Ajustes negativos en la imposición sobre beneficios	f
634	Ajustes negativos en la imposición indirecta	f
6341	Ajustes negativos en IVA de activo corriente	f
6342	Ajustes negativos en IVA de inversiones	f
636	Devolución de impuestos	f
638	Ajustes positivos en la imposición sobre beneficios	f
639	Ajustes positivos en la imposición indirecta	f
6391	Ajustes positivos en IVA de activo corriente	f
6392	Ajustes positivos en IVA de inversiones	f
64	GASTOS DE PERSONAL	f
640	Sueldos y salarios	f
641	Indemnizaciones	f
642	Seguridad Social a cargo de la empresa	f
649	Otros gastos sociales	f
65	OTROS GASTOS DE GESTIÓN	f
650	Pérdidas de créditos comerciales incobrables	f
651	Resultados de operaciones en común	f
6510	Beneficio transferido (gestor)	f
6511	Pérdida soportada (partícipe o asociado no gestor)	f
659	Otras pérdidas en gestión corriente	f
66	GASTOS FINANCIEROS	f
661	Intereses de obligaciones y bonos	f
6610	Intereses de obligaciones y bonos a largo plazo, empresas del grupo	f
6611	Intereses de obligaciones y bonos a largo plazo, empresas asociadas	f
6612	Intereses de obligaciones y bonos a largo plazo, otras partes vinculadas	f
6613	Intereses de obligaciones y bonos a largo plazo, otras empresas	f
6615	Intereses de obligaciones y bonos a corto plazo, empresas del grupo	f
6616	Intereses de obligaciones y bonos a corto plazo, empresas asociadas	f
6617	Intereses de obligaciones y bonos a corto plazo, otras partes vinculadas	f
6618	Intereses de obligaciones y bonos a corto plazo, otras empresas	f
662	Intereses de deudas	f
6620	Intereses de deudas, empresas del grupo	f
6621	Intereses de deudas, empresas asociadas	f
6622	Intereses de deudas, otras partes vinculadas	f
6623	Intereses de deudas con entidades de crédito	f
6624	Intereses de deudas, otras empresas	f
6640	Dividendos de pasivos, empresas del grupo	f
6641	Dividendos de pasivos, empresas asociadas	f
6642	Dividendos de pasivos, otras partes vinculadas	f
6643	Dividendos de pasivos, otras empresas	f
6650	Intereses por descuento de efectos en entidades de crédito del grupo	f
6651	Intereses por descuento de efectos en entidades de crédito asociadas	f
6652	Intereses por descuento de efectos en otras entidades de crédito vinculadas	f
6653	Intereses por descuento de efectos en otras entidades de crédito	f
666	Pérdidas en participaciones y valores representativos de deuda	f
6660	Pérdidas en participaciones y valores representativos de deuda a largo plazo, empresas del grupo	f
6661	Pérdidas en participaciones y valores representativos de deuda a largo plazo, empresas asociadas	f
6662	Pérdidas en participaciones y valores representativos de deuda a largo plazo, otras partes vinculadas	f
6663	Pérdidas en participaciones y valores representativos de deuda a largo plazo, otras empresas	f
6665	Pérdidas en participaciones y valores representativos de deuda a corto plazo, empresas del grupo	f
6666	Pérdidas en participaciones y valores representativos de deuda a corto plazo, empresas asociadas	f
6667	Pérdidas en participaciones y valores representativos de deuda a corto plazo, otras partes vinculadas	f
6668	Pérdidas en participaciones y valores representativos de deuda a corto plazo, de otras empresas	f
667	Pérdidas de créditos no comerciales	f
6670	Pérdidas de créditos a largo plazo, empresas del grupo	f
6671	Pérdidas de créditos a largo plazo, empresas asociadas	f
6672	Pérdidas de créditos a largo plazo, otras partes vinculadas	f
6673	Pérdidas de créditos a largo plazo, otras empresas	f
6675	Pérdidas de créditos a corto plazo, empresas del grupo	f
6676	Pérdidas de créditos a corto plazo, empresas asociadas	f
6677	Pérdidas de créditos a corto plazo, otras partes vinculadas	f
6678	Pérdidas de créditos a corto plazo, de otras empresas	f
668	Diferencias negativas de cambio	f
669	Otros gastos financieros	f
67	PÉRDIDAS PROCEDENTES DE ACTIVOS NO CORRIENTES Y GASTOS EXCEPCIONALES	f
670	Pérdidas procedentes del inmovilizado intangible	f
671	Pérdidas procedentes del inmovilizado material	f
672	Pérdidas procedentes de las inversiones inmobiliarias	f
673	Pérdidas procedentes de participaciones a largo plazo en partes vinculadas	f
6733	Pérdidas procedentes de participaciones a largo plazo, empresas del grupo	f
6734	Pérdidas procedentes de participaciones a largo plazo, empresas asociadas	f
6735	Pérdidas procedentes de participaciones a largo plazo, otras partes vinculadas	f
675	Pérdidas por operaciones con obligaciones propias	f
678	Gastos excepcionales	f
68	DOTACIONES PARA AMORTIZACIONES	f
680	Amortización del inmovilizado intangible	f
681	Amortización del inmovilizado material	f
682	Amortización de las inversiones inmobiliarias	f
69	PÉRDIDAS POR DETERIODO Y OTRAS DOTACIONES	f
690	Pérdidas por deterioro del inmovilizado intangible	f
691	Pérdidas por deterioro del inmovilizado material	f
692	Pérdidas por deterioro de las inversiones inmobiliarias	f
693	Pérdidas por deterioro de existencias	f
6930	Pérdidas por deterioro de productos terminados y en curso de fabricación	f
6931	Pérdidas por deterioro de mercaderías	f
6932	Pérdidas por deterioro de materias primas	f
6933	Pérdidas por deterioro de otros aprovisionamientos	f
695	Dotación a la provisión por operaciones comerciales	f
696	Pérdidas por deterioro de participaciones y valores representativos de deuda a largo plazo	f
6960	Pérdidas por deterioro de participaciones en instrumentos de patrimonio neto a largo plazo, empresas del grupo	f
6961	Pérdidas por deterioro de participaciones en instrumentos de patrimonio neto a largo plazo, empresas asociadas	f
6962	Pérdidas por deterioro de participaciones en instrumentos de patrimonio neto a largo plazo, otras partes vinculadas	f
6963	Pérdidas por deterioro de participaciones en instrumentos de patrimonio neto a largo plazo, otras empresas	f
697	Pérdidas por deterioro de créditos a largo plazo	f
6970	Pérdidas por deterioro de créditos a largo plazo, empresas del grupo	f
6971	Pérdidas por deterioro de créditos a largo plazo, empresas asociadas	f
6972	Pérdidas por deterioro de créditos a largo plazo, otras partes vinculadas	f
6973	Pérdidas por deterioro de créditos a largo plazo, otras empresas	f
698	Pérdidas deterioro de participaciones y valores representativos de deuda a corto plazo	f
6980	Pérdidas por deterioro de participaciones en instrumentos de patrimonio neto a corto plazo, empresas del grupo	f
6981	Pérdidas por deterioro de participaciones en instrumentos de patrimonio neto a corto plazo, empresas asociadas	f
6985	Pérdidas por deterioro en valores representativos de deuda a corto plazo, empresas del grupo	f
6986	Pérdidas por deterioro en valores representativos de deuda a corto plazo, empresas asociadas	f
6987	Pérdidas por deterioro en valores representativos de deuda a corto plazo, otras partes vinculadas	f
6988	Pérdidas por deterioro en valores representativos de deuda a corto plazo, de otras empresas	f
699	Pérdidas por deterioro de créditos a corto plazo	f
7	VENTAS E INGRESOS	f
70	VENTAS DE MERCADERÍAS, DE PRODUCCIÓN PROPIA, DE SERVICIOS, ETC	f
700	Ventas de mercaderías	f
701	Ventas de productos terminados	f
702	Ventas de productos semiterminados	f
703	Ventas de subproductos y residuos	f
704	Ventas de envases y embalajes	f
705	Prestaciones de servicios	f
7063	Descuentos sobre ventas por pronto pago de subproductos y residuos	f
708	Devoluciones de ventas y operaciones similares	f
7080	Devoluciones de ventas de mercaderías	f
7081	Devoluciones de ventas de productos terminados	f
7082	Devoluciones de ventas de productos semiterminados	f
7083	Devoluciones de ventas de subproductos y residuos	f
7084	Devoluciones de ventas de envases y embalajes	f
709	"Rappels" sobre ventas	f
7090	"Rappels" sobre ventas de mercaderias	f
7091	"Rappels" sobre ventas de productos terminados	f
7092	"Rappels" sobre ventas de productos semiterminados	f
7093	"Rappels" sobre ventas de subproductos y residuos	f
7094	"Rappels" sobre ventas de envases y embalajes	f
71	VARIACIÓN DE EXISTENCIAS	f
710	Variación de existencias de productos en curso	f
711	Variación de existencias de productos semiterminados	f
712	Variación de existencias de productos terminados	f
713	Variación de existencias de subproductos, residuos y materiales recuperados	f
73	TRABAJOS REALIZADOS PARA LA EMPRESA	f
730	Trabajos realizados para el inmovilizado intangible	f
731	Trabajos realizados para el inmovilizado material	f
732	Trabajos realizados en inversiones inmobiliarias	f
733	Trabajos realizados para el inmovilizado material en curso	f
74	SUBVENCIONES, DONACIONES Y LEGADOS	f
740	Subvenciones, donaciones y legados a la explotación	f
746	Subvenciones, donaciones y legados de capital transferidas al resultado del ejercicio	f
747	Otras subvenciones, donaciones y legados transferidos al resultado del ejercicio	f
75	OTROS INGRESOS DE GESTIÓN	f
751	Resultados de operaciones en común	f
7510	Pérdida transferida (gestor)	f
7511	Beneficio atribuido (partícipe o asociado no gestor)	f
752	Ingresos por arrendamientos	f
753	Ingresos de propiedad industrial cedida en explotación	f
754	Ingresos por comisiones	f
755	Ingresos por servicios al personal	f
759	Ingresos por servicios diversos	f
76	INGRESOS FINANCIEROS	f
760	Ingresos de participaciones en instrumentos de patrimonio	f
7600	Ingresos de participaciones en instrumentos de patrimonio, empresas del grupo	f
7601	Ingresos de participaciones en instrumentos de patrimonio, empresas asociadas	f
7602	Ingresos de participaciones en instrumentos de patrimonio, otras partes vinculadas	f
7603	Ingresos de participaciones en instrumentos de patrimonio, de otras empresas	f
761	Ingresos de valores representativos de deuda	f
7610	Ingresos de valores representativos de deuda, empresas del grupo	f
7611	Ingresos de valores representativos de deuda, empresas asociadas	f
7612	Ingresos de valores representativos de deuda, otras partes vinculadas	f
7613	Ingresos de valores representativos de deuda, otras empresas	f
762	Ingresos de créditos	f
7620	Ingresos de créditos a largo plazo	f
76200	Ingresos de créditos a largo plazo, empresas del grupo	f
76201	Ingresos de créditos a largo plazo, empresas asociadas	f
76202	Ingresos de créditos a largo plazo, otras partes vinculadas	f
76203	Ingresos de créditos a largo plazo, otras empresas	f
7621	Ingresos de créditos a corto plazo	f
76210	Ingresos de créditos a corto plazo, empresas del grupo	f
76211	Ingresos de créditos a corto plazo, empresas asociadas	f
76212	Ingresos de créditos a corto plazo, otras partes vinculadas	f
76213	Ingresos de créditos a corto plazo, otras empresas	f
768	Diferencias positivas de cambio	f
769	Otros ingresos financieros	f
77	BENEFICIOS PROCEDENTES DE ACTIVOS NO CORRIENTES E INGRESOS EXCEPCIONALES	f
770	Beneficios procedentes del inmovilizado intangible	f
771	Beneficios procedentes del inmovilizado material	f
772	Beneficios procedentes de las inversiones inmobiliarias	f
773	Beneficios procedentes de participaciones a largo plazo en partes vinculadas	f
7733	Beneficios procedentes de participaciones a largo plazo, empresas del grupo	f
7734	Beneficios procedentes de participaciones a largo plazo, empresas asociadas	f
7735	Beneficios procedentes de participaciones a largo plazo, otras partes vinculadas	f
775	Beneficios por operaciones con obligaciones propias	f
778	Ingresos excepcionales.	f
79	EXCESOS Y APLICACIONES DE PROVISIONES Y DE PÉRDIDAS POR DETERIORO	f
790	Reversión del deterioro del inmovilizado intangible	f
791	Reversión del deterioro del inmovilizado material	f
792	Reversión del deterioro de las inversiones inmobiliarias	f
793	Reversión del deterioro de existencias	f
7930	Reversión del deterioro de productos terminados y en curso de fabricación	f
7931	Reversión del deterioro de mercaderias	f
7932	Reversión del deterioro de materias primas	f
7933	Reversión del deterioro de otros aprovisionamientos	f
795	Exceso de provisiones	f
7951	Exceso de provisión para impuestos	f
7952	Exceso de provisión para otras responsabilidades	f
7954	Exceso de provisión pora operaciones comerciales	f
7955	Exceso de provisión para actuaciones medioambientales	f
796	Reversión del deterioro de participaciones y valores representativos de deuda a largo plazo	f
7960	Reversión del deterioro de participaciones en instrumentos de patrimonio neto a largo plazo, empresas del grupo	f
7961	Reversión del deterioro de participaciones en instrumentos de patrimonio neto a largo plazo, empresas asociadas	f
7962	Reversión del deterioro de participaciones en instrumentos de patrimonio neto a largo plazo, otras partes vinculadas	f
7963	Reversión del deterioro de participaciones en instrumentos de patrimonio neto a largo plazo, otras empresas	f
7965	Reversión del deterioro de valores representativos de deuda a largo plazo, empresas del grupo	f
7966	Reversión del deterioro de valores representativos de deuda a largo plazo, empresas asociadas	f
7967	Reversión del deterioro de valores representativos de deuda a largo plazo, otras partes vinculadas	f
797	Reversión del deterioro de créditos a largo plazo	f
7970	Reversión del deterioro de créditos a largo plazo, empresas del grupo	f
7971	Reversión del deterioro de créditos a largo plazo, empresas asociadas	f
7972	Reversión del deterioro de créditos a largo plazo, otras partes vinculadas	f
7973	Reversión del deterioro de créditos a largo plazo, otras empresas	f
798	Reversión del deterioro de participaciones y valores representativos de deuda a corto plazo	f
7980	Reversión del deterioro de participaciones en instrumentos de patrimonio neto a corto plazo, empresas del grupo	f
7981	Reversión del deterioro de participaciones en instrumentos de patrimonio neto a corto plazo, empresas asociadas	f
7985	Reversión del deterioro en valores representativos de deuda a corto plazo, empresas del grupo	f
7986	Reversión del deterioro en valores representativos de deuda a corto plazo, empresas asociadas	f
7987	Reversión del deterioro en valores representativos de deuda a corto plazo, otras partes vinculadas	f
7988	Reversión del deterioro en valores representativos de deuda a corto plazo, de otras empresas	f
799	Reversión del deterioro de créditos a corto plazo	f
10000000	Capital social	f
11200000	Reserva legal	f
12900000	Pérdidas y Ganancias	f
21000001	Terreno local comercial A	f
21100001	Construcción local comercial A	f
28110001	Amort. acumulada construcción local A	f
21600001	Mobiliario diverso	f
21700001	Equipo proceso inforcación PC1	f
28160001	Amort. acumulada mobiliario diverso	f
21700002	Equipo proceso información PC2	f
28170001	Amortización eq. proc. información PC1	f
28170002	Amortización equipo proc. información PC2	f
30000000	Existencias comerciales	f
40000001	Proveedor A	f
40000002	Proveedor B	f
43000001	Cliente A	f
43000002	Cliente B	f
47500000	H.P. acreedora por IVA	f
47520000	H.P. acreedor por IS	f
57000000	Caja, euros	f
68100001	Amortización del inmovilizado material	f
70000000	Ventas de mercaderías	f
47700000	H.P. IVA repercutido	f
60000000	Compras de mercaderías	f
47200000	H.P. Iva soportado	f
47000000	Hacienda pública, deudora por IVA	f
47300001	Pagos a cuenta Impuesto Sociedades	f
11300000	Reservas voluntarias	f
21700003	Equipo proceso información PC3	f
52300001	Proveedor de inmovilizado a CP	f
28170003	Amortización ac. eq.proc. información PC3	f
61000001	Variación existencias mercaderías	f
63000000	Impuesto corriente	f
63010001	Impuesto diferido	f
47900001	Diferencias temporarias imponibles	f
1030	Socios por desembolsos no exigidos, capital social	f
1034	Socios por desembolsos no exigidos, capital pendiente de inscripción	f
1040	Socios por aportaciones no dinerarias pendientes, capital social	f
1044	Socios por aportaciones no dinerarias pendientes, capital pendiente de inscripción	f
1144	Reservas por acciones propias aceptadas en garantía	f
129	Resultado del ejercicio	f
154	Aportaciones no dinerarias pendientes por acciones o participaciones consideradas como pasivos financieros	f
162	Acreedores por arrendamiento financiero a largo plazo, partes vinculadas	f
1623	Acreedores por arrendamiento financiero a largo plazo, empresas del grupo	f
1624	Acreedores por arrendamiento financiero a largo plazo, empresas asociadas	f
1625	Acreedores por arrendamiento financiero a largo plazo, otras partes vinculadas	f
163	Otras deudas a largo plazo con partes vinculadas	f
1633	Otras deudas a largo plazo, empresas del grupo	f
1634	Otras deudas a largo plazo, empresas asociadas	f
1635	Otras deudas a largo plazo, con otras partes vinculadas	f
174	Acreedores por arrendamiento financiero a largo plazo	f
175	Efectos a pagar a largo plazo	f
176	Pasivos por derivados financieros a largo plazo	f
177	Obligaciones y bonos	f
179	Deudas representadas en otros valores negociables	f
181	Anticipos recibidos por ventas o prestaciones de servicios a largo plazo	f
194	Capital emitido pendiente de inscripción	f
195	Acciones o participaciones emitidas consideradas como pasivos financieros	f
197	Suscriptores de acciones consideradas como pasivos financieros	f
199	Acciones o participaciones emitidas consideradas como pasivos financieros pendientes de inscripción	f
200	Investigación	f
201	Desarrollo	f
202	Concesiones administrativas	f
203	Propiedad Industrial	f
205	Derechos de traspaso	f
206	Aplicaciones informáticas	f
24	INVERSIONES FINANCIERAS A LARGO PLAZO EN PARTES VINCULADAS	f
249	Desembolsos pendientes sobre participaciones a largo plazo en partes vinculadas	f
2493	Desembolsos pendientes sobre participaciones a largo plazo en empresas del grupo	f
2494	Desembolsos pendientes sobre participaciones a largo plazo en empresas asociadas	f
2495	Desembolsos pendientes sobre participaciones a largo plazo en otras partes vinculadas	f
259	Desembolsos pendientes sobre participaciones en el patrimonio neto a largo plazo	f
2801	Amortización acumulada de desarrollo	f
2800	Amortización acumulada de investigación	f
2802	Amortización acumulada de concesiones administrativas	f
2803	Amortización acumulada de propiedad industrial	f
2805	Amortización acumulada de derechos de traspaso	f
2806	Amortización acumulada de aplicaciones informáticas	f
29	DETERIORO DE VALOR DE ACTIVOS NO CORRIENTES	f
2900	Deterioro de valor de investigación	f
2901	Deterioro de valor de desarrollo	f
2902	Deterioro de valor de concesiones administrativas	f
2903	Deterioro de valor de propiedad industrial	f
2905	Deterioro de valor de derechos de traspaso	f
2906	Deterioro de valor de aplicaciones informáticas	f
2910	Deterioro de valor de terrenos y bienes naturales	f
2943	Deterioro de valor de valores representativos de deuda a largo plazo de empresas del grupo	f
2944	Deterioro de valor de valores representativos de deuda a largo plazo de empresas asociadas	f
2945	Deterioro de valor de valores representativos de deuda a largo plazo de otras partes vinculadas	f
432	Clientes, operaciones de factoring	f
4332	Clientes empresas del grupo, operaciones de factoring	f
446	Deudores de dudoso cobro	f
479	Pasivos por diferencias temporarias imponibles	f
499	Provisión por operaciones comerciales	f
502	Acciones o participaciones a corto plazo consideradas como pasivos financieros	f
507	Dividendos de acciones o participaciones consideradas como pasivos financieros	f
512	Acreedores por arrendamiento financiero a corto plazo, partes vinculadas	f
5123	Acreedores por arrendamiento financiero a corto plazo, empresas del grupo	f
5124	Acreedores por arrendamiento financiero a corto plazo, empresas asociadas	f
5125	Acreedores por arrendamiento financiero a corto plazo, empresas asociadas	f
513	Otras deudas a corto plazo con empresas del grupo	f
5133	Otras deudas a corto plazo con empresas del grupo	f
5134	Otras deudas a corto plazo con empresas asociadas	f
5135	Otras deudas a corto plazo con otras partes vinculadas	f
514	Intereses a corto plazo de deudas con partes vinculadas	f
5143	Intereses a corto plazo de deudas, empresas del grupo	f
5144	Intereses a corto plazo de deudas, empresas asociadas	f
5145	Intereses a corto plazo de deudas, otras partes vinculadas	f
5209	Deudas por operaciones de factoring	f
524	Acreedores por arrendamiento financiero a corto plazo	f
525	Efectos a pagar a corto plazo	f
526	Dividendo activo a pagar	f
527	Intereses a corto plazo de deudas con entidades de crédito	f
528	Intereses a corto plazo de deudas	f
5291	Provisión a corto plazo para impuestos	f
5293	Provisión a corto plazo por desmantelamiento, retiro o rehabilitación del inmovilizado	f
5292	Provisión a corto plazo para otras responsabilidades	f
5295	Provisión a corto plazo para actuaciones medioambientales	f
533	Intereses a corto plazo de valores representativos de deuda de partes vinculadas	f
5333	Intereses a corto plazo de valores representativos de deuda en empresas del grupo	f
5334	Intereses a corto plazo de valores representativos de deuda en empresas asociadas	f
5335	Intereses a corto plazo de valores representativos de deuda en otras partes vinculadas	f
534	Intereses a corto plazo de créditos a partes vinculadas	f
5343	Intereses a corto plazo de créditos a empresas del grupo	f
5344	Intereses a corto plazo de créditos a empresas asociadas	f
5345	Intereses a corto plazo de créditos a otras partes vinculadas	f
535	Dividendo a cobrar de inversiones financieras en partes vinculadas	f
5353	Dividendo a cobrar de empresas del grupo	f
5354	Dividendo a cobrar de empresas asociadas	f
5355	Dividendo a cobrar de otras partes vinculadas	f
539	Desembolsos pendientes sobre participaciones a corto plazo en partes vinculadas	f
5393	Desembolsos pendientes sobre participaciones a corto plazo en empresas del grupo	f
5394	Desembolsos pendientes sobre participaciones a corto plazo en empresas asociadas	f
5395	Desembolsos pendientes sobre participaciones a corto plazo en otras partes vinculadas	f
546	Intereses a corto plazo de valores representativos de deuda	f
547	Intereses a corto plazo de créditos	f
5580	Socios por desembolsos exigidos sobre acciones o participaciones ordinarias	f
5585	Socios por desembolsos exigidos sobre acciones o participaciones consideradas como pasivos financieros	f
576	Inversiones a corto plazo de gran liquidez	f
59	DETERIORO DEL VALOR DE INVERSIONES FINANCIERAS A CORTO PLAZO	f
660	Gastos financieros por actualización de provisiones	f
663	Pérdidas por valoración de activos y pasivos financieros por su valor razonable	f
664	Dividendos de acciones o participaciones consideradas como pasivos financieros	f
665	Intereses por descuento de efectos y operaciones de factoring	f
6654	Intereses por operaciones de factoring con entidades de crédito del grupo	f
6655	Intereses por operaciones de factoring con entidades de crédito asociadas	f
6656	Intereses por operaciones de factoring con otras entidades de crédito vinculadas	f
6657	Intereses por operaciones de factoring con otras entidades de crédito	f
694	Pérdidas por deterioro de créditos por operaciones comerciales	f
6954	Dotación a la provisión por contratos onerosos	f
6959	Dotación a la provisión por otras operaciones comerciales	f
6965	Pérdidas por deterioro en valores representativos de deuda a largo plazo, empresas del grupo	f
6966	Pérdidas por deterioro en valores representativos de deuda a largo plazo, empresas asociadas	f
6967	Pérdidas por deterioro en valores representativos de deuda a largo plazo, otras partes vinculadas	f
6968	Pérdidas por deterioro en valores representativos de deuda a largo plazo, de otras empresas	f
6990	Pérdidas por deterioro de créditos a corto plazo, empresas del grupo	f
6991	Pérdidas por deterioro de créditos a corto plazo, empresas asociadas	f
6992	Pérdidas por deterioro de créditos a corto plazo, otras partes vinculadas	f
6993	Pérdidas por deterioro de créditos a corto plazo, otras empresas	f
706	Descuentos sobre ventas por pronto pago	f
7060	Descuentos sobre ventas por pronto pago de mercaderias	f
7061	Descuentos sobre ventas por pronto pago de productos terminados	f
7062	Descuentos sobre ventas por pronto pago de productos semiterminados	f
763	Beneficios por la valoración de activos y pasivos financieros por su valor razonable	f
766	Beneficios en participaciones y valores representativos de deuda	f
7660	Beneficios en valores representativos de deuda a largo plazo, empresas del grupo	f
7661	Beneficios en valores representativos de deuda a largo plazo, empresas asociadas	f
7662	Beneficios en valores representativos de deuda a largo plazo, otras partes vinculadas	f
7663	Beneficios en participaciones y valores representativos de deuda a largo plazo, otras empresas	f
7665	Beneficios en participaciones y valores representativos de deuda a corto plazo, empresas del grupo	f
7666	Beneficios en participaciones y valores representativos de deuda a corto plazo, empresas asociadas	f
7667	Beneficios en valores representativos de deuda a corto plazo, otras partes vinculadas	f
7668	Beneficios en valores representativos de deuda a corto plazo, de otras empresas	f
794	Reversión del deterioro de créditos por operaciones comerciales	f
79544	Exceso de provisión por contratos onerosos	f
79549	Exceso de provisión por otras operaciones comerciales	f
7968	Reversión del deterioro de valores representativos de deuda a largo plazo, otras empresas	f
7990	Reversión del deterioro de créditos a corto plazo, empresas del grupo	f
7991	Reversión del deterioro de créditos a corto plazo, empresas asociadas	f
7992	Reversión del deterioro de créditos a corto plazo, otras partes vinculadas	f
7993	Reversión del deterioro de créditos a corto plazo, otras empresas	f
\.


--
-- Data for Name: presupuesto; Type: TABLE DATA; Schema: public; Owner: pepe
--

COPY presupuesto (ejercicio, cuenta, ejerciciobase, presupuestobase, base, base1, base2, base3, base4, base5, base6, base7, base8, base9, base10, base11, base12, base13, base14, base15, presupuesto, presupuesto1, presupuesto2, presupuesto3, presupuesto4, presupuesto5, presupuesto6, presupuesto7, presupuesto8, presupuesto9, presupuesto10, presupuesto11, presupuesto12, presupuesto13, presupuesto14, presupuesto15) FROM stdin;
\.


--
-- Data for Name: saldossubcuenta; Type: TABLE DATA; Schema: public; Owner: pepe
--

COPY saldossubcuenta (codigo, saldo, saldomedio1, saldomedio2) FROM stdin;
28160002	0.00	0.00	0.00
40000002	0.00	0.00	0.00
40000001	0.00	0.00	0.00
47000000	0.00	0.00	0.00
52300001	0.00	0.00	0.00
43000001	0.00	0.00	0.00
47200000	0.00	0.00	0.00
43000002	0.00	0.00	0.00
47700000	0.00	0.00	0.00
47300001	0.00	0.00	0.00
68100001	0.00	0.00	0.00
70000000	0.00	0.00	0.00
60000000	0.00	0.00	0.00
61000001	0.00	0.00	0.00
63000000	0.00	0.00	0.00
63010001	0.00	0.00	0.00
10000000	0.00	0.00	0.00
11200000	0.00	0.00	0.00
12900000	0.00	0.00	0.00
21000001	0.00	0.00	0.00
21100001	0.00	0.00	0.00
28110001	0.00	0.00	0.00
21600001	0.00	0.00	0.00
21700001	0.00	0.00	0.00
28160001	0.00	0.00	0.00
21700002	0.00	0.00	0.00
28170001	0.00	0.00	0.00
28170002	0.00	0.00	0.00
30000000	0.00	0.00	0.00
47500000	0.00	0.00	0.00
47520000	0.00	0.00	0.00
57000000	0.00	0.00	0.00
11300000	0.00	0.00	0.00
21700003	0.00	0.00	0.00
28170003	0.00	0.00	0.00
47900001	0.00	0.00	0.00
\.


--
-- Data for Name: tiposiva; Type: TABLE DATA; Schema: public; Owner: pepe
--

COPY tiposiva (clave, tipo, re, descripcion) FROM stdin;
GN	16.00	0.00	TIPO GENERAL
GN2	16.00	4.00	TIPO GENERAL CON RECARGO DE EQUIVALENCIA
RD	7.00	0.00	TIPO REDUCIDO
RD2	7.00	1.00	TIPO REDUCIDO CON RECARGO DE EQUIVALENCIA
SRD	4.00	0.00	TIPO SUPERREDUCIDO
SRD2	4.00	0.50	TIPO SUPERREDUCIDO CON RECARGO DE EQUIVALENCIA
\.


--
-- Data for Name: var_as_modelo; Type: TABLE DATA; Schema: public; Owner: pepe
--

COPY var_as_modelo (asientomodelo, variable, tipo, descripcion, orden) FROM stdin;
\.


--
-- Data for Name: vencimientos; Type: TABLE DATA; Schema: public; Owner: pepe
--

COPY vencimientos (num, cta_ordenante, fecha_operacion, importe, cuenta_tesoreria, fecha_vencimiento, derecho, pendiente, anulado, pase_diario_operacion, pase_diario_vencimiento, usuario, concepto) FROM stdin;
1	43000001	2008-08-01	500.00	57000000	2008-01-10	t	f	f	16	23	pepe	
6	43000001	2008-01-10	116.00	57000000	2008-01-10	t	f	f	25	28	pepe	
2	43000002	2008-08-01	400.00	57000000	2008-01-16	t	f	f	17	30	pepe	
3	40000001	2008-08-01	1500.00	57000000	2008-01-20	f	f	f	14	32	pepe	
5	40000002	2008-08-01	1500.00	57000000	2008-02-05	f	f	f	15	34	pepe	
4	40000001	2008-08-01	500.00	57000000	2008-02-10	f	f	f	14	36	pepe	
7	43000002	2008-03-15	174.00	57000000	2008-03-15	t	f	f	38	41	pepe	
8	40000001	2008-03-16	1160.00	57000000	2008-03-16	f	f	f	45	46	pepe	
9	43000001	2008-04-20	568.40	57000000	2008-04-20	t	f	f	53	56	pepe	
10	43000002	2008-06-10	580.00	57000000	2008-06-10	t	f	f	58	61	pepe	
11	43000001	2008-07-20	5800.00	57000000	2008-07-20	t	f	f	76	79	pepe	
12	43000002	2008-11-10	2320.00	57000000	2008-11-10	t	f	f	92	93	pepe	
\.


--
-- Name: amortcontable_pkey; Type: CONSTRAINT; Schema: public; Owner: pepe; Tablespace: 
--

ALTER TABLE ONLY amortcontable
    ADD CONSTRAINT amortcontable_pkey PRIMARY KEY (ejercicio);


--
-- Name: amortfiscalycontable_pkey; Type: CONSTRAINT; Schema: public; Owner: pepe; Tablespace: 
--

ALTER TABLE ONLY amortfiscalycontable
    ADD CONSTRAINT amortfiscalycontable_pkey PRIMARY KEY (ejercicio, cuenta_activo);


--
-- Name: amortpers_pkey; Type: CONSTRAINT; Schema: public; Owner: pepe; Tablespace: 
--

ALTER TABLE ONLY amortpers
    ADD CONSTRAINT amortpers_pkey PRIMARY KEY (cuenta, ejercicio);


--
-- Name: cab_as_modelo_pkey; Type: CONSTRAINT; Schema: public; Owner: pepe; Tablespace: 
--

ALTER TABLE ONLY cab_as_modelo
    ADD CONSTRAINT cab_as_modelo_pkey PRIMARY KEY (asientomodelo);


--
-- Name: cabeceraestados_pkey; Type: CONSTRAINT; Schema: public; Owner: pepe; Tablespace: 
--

ALTER TABLE ONLY cabeceraestados
    ADD CONSTRAINT cabeceraestados_pkey PRIMARY KEY (titulo);


--
-- Name: ci_amort_pkey; Type: CONSTRAINT; Schema: public; Owner: pepe; Tablespace: 
--

ALTER TABLE ONLY ci_amort
    ADD CONSTRAINT ci_amort_pkey PRIMARY KEY (cuenta, ci);


--
-- Name: ci_pkey; Type: CONSTRAINT; Schema: public; Owner: pepe; Tablespace: 
--

ALTER TABLE ONLY ci
    ADD CONSTRAINT ci_pkey PRIMARY KEY (codigo, nivel);


--
-- Name: conceptos_pkey; Type: CONSTRAINT; Schema: public; Owner: pepe; Tablespace: 
--

ALTER TABLE ONLY conceptos
    ADD CONSTRAINT conceptos_pkey PRIMARY KEY (clave);


--
-- Name: cuenta_ext_conci_pkey; Type: CONSTRAINT; Schema: public; Owner: pepe; Tablespace: 
--

ALTER TABLE ONLY cuenta_ext_conci
    ADD CONSTRAINT cuenta_ext_conci_pkey PRIMARY KEY (numero);


--
-- Name: datossubcuenta_pkey; Type: CONSTRAINT; Schema: public; Owner: pepe; Tablespace: 
--

ALTER TABLE ONLY datossubcuenta
    ADD CONSTRAINT datossubcuenta_pkey PRIMARY KEY (cuenta);


--
-- Name: diario_pkey; Type: CONSTRAINT; Schema: public; Owner: pepe; Tablespace: 
--

ALTER TABLE ONLY diario
    ADD CONSTRAINT diario_pkey PRIMARY KEY (pase);


--
-- Name: diarios_pkey; Type: CONSTRAINT; Schema: public; Owner: pepe; Tablespace: 
--

ALTER TABLE ONLY diarios
    ADD CONSTRAINT diarios_pkey PRIMARY KEY (codigo);


--
-- Name: dif_conciliacion_pkey; Type: CONSTRAINT; Schema: public; Owner: pepe; Tablespace: 
--

ALTER TABLE ONLY dif_conciliacion
    ADD CONSTRAINT dif_conciliacion_pkey PRIMARY KEY (codigo);


--
-- Name: ejercicios_pkey; Type: CONSTRAINT; Schema: public; Owner: pepe; Tablespace: 
--

ALTER TABLE ONLY ejercicios
    ADD CONSTRAINT ejercicios_pkey PRIMARY KEY (codigo);


--
-- Name: equivalenciasplan_pkey; Type: CONSTRAINT; Schema: public; Owner: pepe; Tablespace: 
--

ALTER TABLE ONLY equivalenciasplan
    ADD CONSTRAINT equivalenciasplan_pkey PRIMARY KEY (cod);


--
-- Name: estados_pkey; Type: CONSTRAINT; Schema: public; Owner: pepe; Tablespace: 
--

ALTER TABLE ONLY estados
    ADD CONSTRAINT estados_pkey PRIMARY KEY (titulo, nodo, parte1);


--
-- Name: libroiva_pkey; Type: CONSTRAINT; Schema: public; Owner: pepe; Tablespace: 
--

ALTER TABLE ONLY libroiva
    ADD CONSTRAINT libroiva_pkey PRIMARY KEY (pase);


--
-- Name: nuevoplan_pkey; Type: CONSTRAINT; Schema: public; Owner: pepe; Tablespace: 
--

ALTER TABLE ONLY nuevoplan
    ADD CONSTRAINT nuevoplan_pkey PRIMARY KEY (codigo);


--
-- Name: periodos_pkey; Type: CONSTRAINT; Schema: public; Owner: pepe; Tablespace: 
--

ALTER TABLE ONLY periodos
    ADD CONSTRAINT periodos_pkey PRIMARY KEY (ejercicio, codigo);


--
-- Name: planamortizaciones_pkey; Type: CONSTRAINT; Schema: public; Owner: pepe; Tablespace: 
--

ALTER TABLE ONLY planamortizaciones
    ADD CONSTRAINT planamortizaciones_pkey PRIMARY KEY (cuenta_activo);


--
-- Name: plancontable_pkey; Type: CONSTRAINT; Schema: public; Owner: pepe; Tablespace: 
--

ALTER TABLE ONLY plancontable
    ADD CONSTRAINT plancontable_pkey PRIMARY KEY (codigo);


--
-- Name: presupuesto_pkey; Type: CONSTRAINT; Schema: public; Owner: pepe; Tablespace: 
--

ALTER TABLE ONLY presupuesto
    ADD CONSTRAINT presupuesto_pkey PRIMARY KEY (ejercicio, cuenta);


--
-- Name: saldossubcuenta_pkey; Type: CONSTRAINT; Schema: public; Owner: pepe; Tablespace: 
--

ALTER TABLE ONLY saldossubcuenta
    ADD CONSTRAINT saldossubcuenta_pkey PRIMARY KEY (codigo);


--
-- Name: tiposiva_pkey; Type: CONSTRAINT; Schema: public; Owner: pepe; Tablespace: 
--

ALTER TABLE ONLY tiposiva
    ADD CONSTRAINT tiposiva_pkey PRIMARY KEY (clave);


--
-- Name: var_as_modelo_pkey; Type: CONSTRAINT; Schema: public; Owner: pepe; Tablespace: 
--

ALTER TABLE ONLY var_as_modelo
    ADD CONSTRAINT var_as_modelo_pkey PRIMARY KEY (asientomodelo, variable);


--
-- Name: vencimientos_pkey; Type: CONSTRAINT; Schema: public; Owner: pepe; Tablespace: 
--

ALTER TABLE ONLY vencimientos
    ADD CONSTRAINT vencimientos_pkey PRIMARY KEY (num);


--
-- Name: cuenta; Type: INDEX; Schema: public; Owner: pepe; Tablespace: 
--

CREATE INDEX cuenta ON diario USING btree (cuenta);


--
-- Name: public; Type: ACL; Schema: -; Owner: postgres
--

REVOKE ALL ON SCHEMA public FROM PUBLIC;
REVOKE ALL ON SCHEMA public FROM postgres;
GRANT ALL ON SCHEMA public TO postgres;
GRANT ALL ON SCHEMA public TO PUBLIC;


--
-- PostgreSQL database dump complete
--

