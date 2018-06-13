package com.capirott.erick.veeraschat.core.friend.get.all;

import com.capirott.erick.veeraschat.models.User;

import java.util.List;


public interface GetFriendsContract {
    interface View {
        void onGetAllFriendsSuccess(List<User> users);

        void onGetAllFriendsFailure(String message);

    }

    interface Presenter {
        void getAllFriends(String userId);
    }

    interface Interactor {
        void getAllFriendsFromFirebase(String userId);
    }

    interface OnGetAllFriendsListener {
        void onGetAllFriendsSuccess(List<User> users);

        void onGetAllFriendsFailure(String message);
    }

}
