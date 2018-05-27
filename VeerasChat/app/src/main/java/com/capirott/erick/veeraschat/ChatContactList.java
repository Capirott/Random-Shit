package com.capirott.erick.veeraschat;

import java.util.Collection;

class ChatContactList {

    String userId;

    Collection<String> contactsId;

    public String getUserId() {
        return userId;
    }

    public void setUserId(String userId) {
        this.userId = userId;
    }

    public Collection<String> getContactsId() {
        return contactsId;
    }

    public void setContactsId(Collection<String> contactsId) {
        this.contactsId = contactsId;
    }
}
