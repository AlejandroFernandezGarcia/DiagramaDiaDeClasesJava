package es.udc.fi.dc.photoalbum.model.hibernate;

import java.io.Serializable;
import java.util.Calendar;
import java.util.HashSet;
import java.util.Set;
import es.udc.fi.dc.photoalbum.util.utils.ComparableById;
import es.udc.fi.dc.photoalbum.util.utils.PrivacyLevel;

public class Album {
    private Integer id;
    private String name;
    private User user;
    private Calendar date;
    private String privacyLevel;
    private LikeAndDislike likeAndDislike;

    public User getUser() {
        return user;
    }

    public void setUser(User user) {
        this.user = user;
    }

    public Calendar getDate() {
        return date;
    }

    public void setDate(Calendar date) {
        this.date = date;
    }

    public String getPrivacyLevel() {
        return privacyLevel;
    }

    public void setPrivacyLevel(String privacyLevel) {
        this.privacyLevel = privacyLevel;
    }

    public Integer getId() {
        return id;
    }

    public void setId(Integer id) {
        this.id = id;
    }

}
