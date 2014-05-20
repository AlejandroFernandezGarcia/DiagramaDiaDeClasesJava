package modelo.fuentesInformacion;

import java.io.Serializable;
import java.util.Calendar;
import modelo.referencias.Autor;

public class Revista extends FuenteInformacion{

    private String editorial;

    public String getEditorial() {
        return editorial;
    }

    public void setEditorial(String editorial) {
        this.editorial = editorial;
    }

}

