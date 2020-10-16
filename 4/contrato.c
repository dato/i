#include <stdbool.h>

enum mes {
    ENERO = 1,
    FEBRERO,
    MARZO,
    ABRIL,
    MAYO,
    JUNIO,
    JULIO,
    AGOSTO,
    SEPTIEMBRE,
    OCTUBRE,
    NOVIEMBRE,
    DICIEMBRE,
};

struct fecha_contrato {
    int mes;
    int ano;
};

// Calcula la duración, en meses, del contrato actual.
int calcular_duracion(struct fecha_contrato *fecha);

// La función contrato_vencido() devuelva verdadero si un contrato
// de alquiler está vencido, o falso en caso contrario.
//
// Nota: un contrato está vencido si han pasado más de 36 meses desde
// su firma; o, si se firmó anteriormente a 7/2020, más de 24 meses.


// Versión 1 (❌❌)
bool contrato_vencido1(struct fecha_contrato *fecha_firma) {
    int duracion = calcular_duracion(fecha_firma);
    bool ok;

    if (fecha_firma->ano < 2020) {
        if (duracion <= 24)
            ok = true;
        else
            ok = false;
    }
    else if (fecha_firma->ano > 2020) {
        if (duracion <= 36)
            ok = true;
        else
            ok = false;
    }
    else if (fecha_firma->mes < JULIO) {
        if (duracion <= 36)
            ok = true;
        else
            ok = false;
    }
    else {
        if (duracion <= 24)
            ok = true;
        else
            ok = false;
    }

    return ok;
}


// Versión 2 (❌)
bool contrato_vencido2(struct fecha_contrato *fecha_firma) {
    int duracion = calcular_duracion(fecha_firma);
    bool vencido = false;

    if (fecha_firma->ano < 2020) {
        if (duracion > 24)
            vencido = true;
    }
    else if (fecha_firma->ano > 2020) {
        if (duracion > 36)
            vencido = true;
    }
    else if (fecha_firma->mes < JULIO) {
        if (duracion > 36)
            vencido = true;
    }
    else {
        if (duracion > 24)
            vencido = true;
    }

    return vencido;
}


// Versión 3 (✓)
bool contrato_vencido3(struct fecha_contrato *fecha_firma) {
    int duracion = calcular_duracion(fecha_firma);
    bool vencido;

    // Verificamos si es contrato antiguo.
    if (fecha_firma->ano < 2020 ||
        (fecha_firma->ano == 2020 && fecha_firma->mes < JULIO)) {
        vencido = (duracion > 24);
    }
    else {
        vencido = (duracion > 36);
    }

    return vencido;
}


// Versión 4 (✓✓)
bool contrato_vencido4(struct fecha_contrato *firmado) {
    int duracion = calcular_duracion(firmado);

    if (firmado->ano < 2020 || (firmado->ano == 2020 && firmado->mes < JULIO)) {
        return duracion > 24;  // Es un contrato antiguo.
    }

    return duracion > 36;
}


// Versión 5 (✓?)
bool contrato_vencido(struct fecha_contrato *firma) {
    bool old = firma->ano < 2020 || (firma->ano == 2020 && firma->mes < JULIO);

    int actual = calcular_duracion(firma);
    int permitida = old ? 24 : 36;

    return actual > permitida;
}
