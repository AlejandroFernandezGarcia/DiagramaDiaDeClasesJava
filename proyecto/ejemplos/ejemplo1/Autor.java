package pl;

import java.util.Calendar;

public class Autor{

    private String nombre;
    private Calendar fechaNacimiento;
    private int sueldo;
    private List<Libro> listaLibros;
    
    public String getNombre(){
    	this.nombre = nombre;
    }
    
    public void setNombre(String nombre){
    	this.nombre = nombre;
    }
}
