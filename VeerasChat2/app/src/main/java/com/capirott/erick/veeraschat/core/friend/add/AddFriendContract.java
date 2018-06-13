package com.capirott.erick.veeraschat.core.friend.add;

import android.content.Context;

import com.capirott.erick.veeraschat.models.User;


public interface AddFriendContract {
    interface View {
        void onAddFriendSuccess(String message);

        void onAddFriendFailure(String message);
    }

    interface Presenter {
        void addFriend(final Context context, final String userId, final String userId2);
    }

    interface Interactor {
        void addFriendToDatabase(final Context context, final String userId, final String userId2);
    }

    interface OnFriendDatabaseListener {
        void onSuccess(String message);

        void onFailure(String message);
    }
}
