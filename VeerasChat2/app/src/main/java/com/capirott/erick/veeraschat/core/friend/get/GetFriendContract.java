package com.capirott.erick.veeraschat.core.friend.get;

import android.content.Context;


public interface GetFriendContract {
    interface View {
        void onGetFriendSuccess(String message);

        void onGetFriendFailure(String message);
    }

    interface Presenter {
        void friendShipExists(final Context context, final String userId, final String userId2);
    }

    interface Interactor {
        void friendShipExists(final Context context, final String userId, final String userId2);
    }

    interface OnFriendDatabaseListener {
        void onSuccess(String message);

        void onFailure(String message);
    }
}
