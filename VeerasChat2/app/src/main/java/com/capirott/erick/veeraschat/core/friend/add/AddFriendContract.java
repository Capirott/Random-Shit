package com.capirott.erick.veeraschat.core.friend.add;

import android.content.Context;

import com.capirott.erick.veeraschat.models.User;


public interface AddFriendContract {
    interface View {
        void onAddFriendSuccess(String message);

        void onAddFriendFailure(String message);
    }

    interface Presenter {
        void addFriend(Context context, User user);
    }

    interface Interactor {
        void addFriendToDatabase(Context context, User user);
    }

    interface OnFriendDatabaseListener {
        void onSuccess(String message);

        void onFailure(String message);
    }
}
