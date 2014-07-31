package es.udc.fi.dc.photoalbum.model.hibernate;

import java.util.ArrayList;
import java.util.Calendar;
import java.util.List;

import org.hibernate.Criteria;
import org.hibernate.Query;
import org.hibernate.criterion.DetachedCriteria;
import org.hibernate.criterion.Restrictions;
import org.springframework.orm.hibernate3.support.HibernateDaoSupport;

import es.udc.fi.dc.photoalbum.util.utils.PrivacyLevel;

public class AlbumDaoImpl extends AlbumDao,Serializable implements AlbumDao{

    private String DATE;
    private String LIKE;
    private Album album;
    
    
    private Query createQuery(String hql) {
    }

    public void create(Album album) {
    }

    public void delete(Album album) {
    }

    public Album getAlbum(String name, int userId) {  
    }

    public void rename(Album album, String newName) {
    }

    public Album getById(Integer id) {
    }

    public void changePrivacyLevel(Album album, String privacyLevel) {
    }

    public List<Album> getAlbumsByTag(int userId, String tag) {
    }

}
