package pepito;

import pepe.lacasitos;

public abstract class Autor implements Hoja{

    private String nombre;
    private Calendar fechaNacimiento;
    private int sueldo;
    private Libro libro;
    
    public String getNombre(){
    	this.nombre = nombre;
    }
    
    public void setNombre(String nombre){
    	this.nombre = nombre;
    }
}
