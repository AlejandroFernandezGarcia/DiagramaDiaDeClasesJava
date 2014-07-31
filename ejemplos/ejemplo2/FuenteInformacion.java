package modelo.fuentesInformacion;

import java.io.Serializable;
import java.util.Calendar;

public abstract class FuenteInformacion{

    private String nombreFuente;
    private long calidad;
    private Calendar fecha;
    private Autor autor;

    public String getNombreFuente() {
        return nombreFuente;
    }
}

