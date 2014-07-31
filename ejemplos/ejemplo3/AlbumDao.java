package es.udc.fi.dc.photoalbum.model.hibernate;

import java.util.Calendar;
import java.util.List;

import es.udc.fi.dc.photoalbum.util.utils.PrivacyLevel;

public interface AlbumDao{

    void rename(Album album, String newName);

    void changePrivacyLevel(Album album, String privacyLevel);

    Album getById(Integer id);

    Album getAlbum(String name, int userId);

    Album getSharedAlbum(String albumName, int userSharedToId,
            String userSharedEmail);
}
