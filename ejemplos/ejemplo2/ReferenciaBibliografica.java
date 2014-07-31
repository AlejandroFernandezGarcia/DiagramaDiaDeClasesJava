package modelo.referencias;

import modelo.formatos.Formato;
import java.io.Serializable;
import java.util.Calendar;

public class ReferenciaBibliografica{
	private String tipo;
	private Calendar ano;
	private String nFReferenciada;
	private Autor autor;
	private Formato formato;  
	private FuenteInformacion FI;
        
	public String getTipo() {
	  return tipo;
	}

	public void setTipo(String tipo) {
	  this.tipo = tipo;
	}

	public String getCodigo() {
	  return nombreFuenteReferenciada;
	}

	public void setCodigo(String nFReferenciada) {
	  this.nFReferenciada = nFReferenciada;
	}

	public Calendar getAno() {
	  return ano;
	}

	public void setAno(Calendar ano) {
	  this.ano = ano;
	}

	public Autor getAutor() {
	  return autor;
	}

	public void setAutor(Autor autor) {
	  this.autor = autor;
	}

	public Formato getFormato() {
	  return formato;
	}

	public void setFormato(Formato formato) {
	  this.formato = formato;
	}

}

