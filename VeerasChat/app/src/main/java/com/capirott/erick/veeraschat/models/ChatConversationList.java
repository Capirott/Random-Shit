package com.capirott.erick.veeraschat.models;

import java.util.Collection;

class ChatConversationList {

    String userId;

    Collection<String> converstationsId;

    public String getUserId() {
        return userId;
    }

    public void setUserId(String userId) {
        this.userId = userId;
    }

    public Collection<String> getConverstationsId() {
        return converstationsId;
    }

    public void setConverstationsId(Collection<String> converstationsId) {
        this.converstationsId = converstationsId;
    }

    public void addConversation(ChatConversation conversation) {
        converstationsId.add(conversation.getId());
    }
}
