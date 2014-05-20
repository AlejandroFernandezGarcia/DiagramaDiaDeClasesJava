package modelo.fuentesInformacion;

import java.io.Serializable;
import java.util.Calendar;
import modelo.referencias.Autor;

public class Congreso extends FuenteInformacion{

    private String localizacion;

    public String getLocalizacion() {
        return localizacion;
    }

    public void setLocalizacion(String localizacion) {
        this.localizacion = localizacion;
    }

}

