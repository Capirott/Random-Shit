package com.capirott.erick.veeraschat.core.friend.get;

import android.content.Context;


public class GetFriendPresenter implements GetFriendContract.Presenter, GetFriendContract.OnFriendDatabaseListener {
        private GetFriendContract.View mView;
    private GetFriendInteractor mGetFriendInteractor;

    public GetFriendPresenter(GetFriendContract.View view) {
        this.mView = view;
        mGetFriendInteractor = new GetFriendInteractor(this);
    }

    @Override
    public void friendShipExists(final Context context, final String userId, final String userId2) {
        mGetFriendInteractor.friendShipExists(context, userId, userId2);
    }

    @Override
    public void onSuccess(String message) {
        mView.onGetFriendSuccess(message);
    }

    @Override
    public void onFailure(String message) {
        mView.onGetFriendFailure(message);
    }
}
